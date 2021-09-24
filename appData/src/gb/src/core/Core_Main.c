#include "Core_Main.h"

#include <gb/cgb.h>
#include <string.h>
#include <rand.h>

#include "Actor.h"
#include "BankManager.h"
#include "Camera.h"
#include "DataManager.h"
#include "FadeManager.h"
#include "GameTime.h"
#include "Input.h"
#include "MusicManager.h"
#include "Palette.h"
#include "Projectiles.h"
#include "ScriptRunner.h"
#include "Scroll.h"
#include "Sprite.h"
#include "UI.h"
#include "gbt_player.h"
#include "data_ptrs.h"
#include "main.h"
#include "states/ZeldasAdventure.h"

UBYTE game_time = 0;
UBYTE seedRand = 2;
UINT16 next_state;
UINT8 delta_time;
UINT16 current_state;
UINT8 state_running = 0;
UINT8 vbl_count = 0;
INT16 old_scroll_x, old_scroll_y;
UINT8 music_mute_frames = 0;

extern SCENE_STATE scene_stack;

UINT8 ZELDA_HUD_BLANK = 0xff;
UINT8 ZELDA_HUD_1 = 0xff;
UINT8 ZELDA_HUD_2 = 0xff;
UINT8 ZELDA_HUD_3 = 0xff;
UINT8 ZELDA_HUD_4 = 0xff;
UINT8 ZELDA_HUD_5 = 0xff;
UINT8 ZELDA_HUD_6 = 0xff;
UINT8 ZELDA_HUD_7 = 0xff;
UINT8 ZELDA_HUD_8 = 0xff;
UINT8 ZELDA_HUD_9 = 0xff;
UINT8 ZELDA_HUD_0 = 0xff;
UINT8 ZELDA_HUD_RUPEE = 0xff;
UINT8 ZELDA_HUD_HEART_EMPTY = 0xff;
UINT8 ZELDA_HUD_HEART_HALF = 0xff;
UINT8 ZELDA_HUD_HEART_FULL = 0xff;

UINT8 *ptrBlank = (UINT8 *)0xcd40;
UINT8 *ptr1 = (UINT8 *)0xcd41;
UINT8 *ptr2 = (UINT8 *)0xcd42;
UINT8 *ptr3 = (UINT8 *)0xcd43;
UINT8 *ptr4 = (UINT8 *)0xcd44;
UINT8 *ptr5 = (UINT8 *)0xcd45;
UINT8 *ptr6 = (UINT8 *)0xcd46;
UINT8 *ptr7 = (UINT8 *)0xcd47;
UINT8 *ptr8 = (UINT8 *)0xcd48;
UINT8 *ptr9 = (UINT8 *)0xcd49;
UINT8 *ptr0 = (UINT8 *)0xcd4a;
UINT8 *ptrRupee = (UINT8 *)0xcd4b;
UINT8 *ptrHeartEmpty = (UINT8 *)0xcd4c;
UINT8 *ptrHeartHalf = (UINT8 *)0xcd4d;
UINT8 *ptrHeartFull = (UINT8 *)0xcd4e;

BYTE ZELDA_TILES_FOUND = 0;

unsigned char zeldasAdventureHudMap[20] = {0x00, 0x0B, 0x0A, 0x0A, 0x0A, 0x00, 0x0E,
                                           0x0E, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
                                           0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C};
// for 3 hearts the starting point for rendering is tile 16
const UINT8 HEART_START_DRAW = 16;
// pointer to GB Studio variables $00 and $01
UINT8 *cachedHealth = (UINT8 *)0xcd2a;
UINT8 *health = (UINT8 *)0xcd2b;
// pointer to GB Studio variables $02 and $03
UINT8 *cachedMaxHearts = (UINT8 *)0xcd2c;
UINT8 *maxHearts = (UINT8 *)0xcd2d;
// pointer to GB Studio variables $04 and $05
UINT8 *cachedRupees = (UINT8 *)0xcd2e;
UINT8 *rupees = (UINT8 *)0xcd2f;

/**
 * Takes a number and returns the associated tile image
 */
UINT8 GetNumberTile(UINT8 number)
{
    switch (number)
    {
    case 0:
        return ZELDA_HUD_0;
        break;
    case 1:
        return ZELDA_HUD_1;
        break;
    case 2:
        return ZELDA_HUD_2;
        break;
    case 3:
        return ZELDA_HUD_3;
        break;
    case 4:
        return ZELDA_HUD_4;
        break;
    case 5:
        return ZELDA_HUD_5;
        break;
    case 6:
        return ZELDA_HUD_6;
        break;
    case 7:
        return ZELDA_HUD_7;
        break;
    case 8:
        return ZELDA_HUD_8;
        break;
    case 9:
        return ZELDA_HUD_9;
        break;

    default:
        return ZELDA_HUD_BLANK;
        break;
    }
}

/**
 * Draws the HUD rupee counter for a given value
 */
void CalculateRupees(char *hud, UINT8 rupees)
{
    UINT8 count = 1;
    while (rupees > 0)
    {
        UINT8 digit = rupees % 10;
        // set the hundreds
        if (count == 3)
        {
            hud[2] = GetNumberTile(digit);
        }
        // set the tens
        if (count == 2)
        {
            hud[3] = GetNumberTile(digit);
        }
        // set the units
        if (count == 1)
        {
            hud[4] = GetNumberTile(digit);
        }

        rupees /= 10;
        count++;
    }
}

/**
 * Draws the HUD hearts/health values
 */
void CalculateHearts(char *hud, UINT8 maxHearts, UINT8 health)
{
    // max hearts is 14
    // max health is 28 (2 half hearts)
    UINT8 healthCounter = health;
    UINT8 startDraw = HEART_START_DRAW - maxHearts + 3;

    for (UINT8 i = 6; i < 19; i++)
    {
        if (i < startDraw)
        {
            hud[i] = ZELDA_HUD_BLANK;
        }
        else if (healthCounter > 2)
        {
            hud[i] = ZELDA_HUD_HEART_FULL;
            healthCounter -= 2;
            continue;
        }
        else if (healthCounter == 2)
        {
            hud[i] = ZELDA_HUD_HEART_FULL;
            healthCounter -= 2;
            continue;
        }
        else if (healthCounter == 1)
        {
            hud[i] = ZELDA_HUD_HEART_HALF;
            healthCounter--;
            continue;
        }
        else
        {
            hud[i] = ZELDA_HUD_HEART_EMPTY;
        }
    }

    // special case for last heart as we nornally leave the last tile empty
    if (maxHearts == 14)
    {
        if (health == 28)
        {
            hud[19] = ZELDA_HUD_HEART_FULL;
        }
        else if (health == 27)
        {
            hud[19] = ZELDA_HUD_HEART_HALF;
        }
        else
        {
            hud[19] = ZELDA_HUD_HEART_EMPTY;
        }
    }
    else
    {
        hud[19] = ZELDA_HUD_BLANK;
    }
}

/**
 * Updates the rupee and hearts HUD based on provided values
 */
void CalculateHud(char *hud, UINT8 rupees, UINT8 maxHearts, UINT8 health, BYTE heartsChanged, BYTE maxHeartsChanged, BYTE rupeesChanged)
{
    // set the rupee count
    if(rupeesChanged) {    
        CalculateRupees(hud, rupees);
    }

    // set the hearts
    if(heartsChanged || maxHeartsChanged) { 
        CalculateHearts(hud, maxHearts, health);
    }
}

void UpdateZeldaHud(BYTE heartsChanged, BYTE maxHeartsChanged, BYTE rupeesChanged) {
//   CalculateHud(zeldasAdventureHudMap, *rupees, *maxHearts, *health, heartsChanged, maxHeartsChanged, rupeesChanged);
  set_bkg_tiles(0, 0, 20, 1, zeldasAdventureHudMap);
}

BYTE IsZeldasAdventureTypeScene() {
    return scene_type == ZELDAS_ADVENTURE_SCENE_TYPE;
}

/**
 * All Zelda Adventure scenes have the necessary HUD elements in the first row of the scene
 * As their location in tile memory can change we need to find and store their location before 
 * attempting to draw the HUD
 */
void FindTilesInVram(char *hud)
{
    if(!ZELDA_TILES_FOUND) {
        BYTE found = 0;

        // for some reason copying the tile numbers from tile RAM is very incosistent
        // so we need to retry until we've got 'em all!
        while(found == 0) {
            if(ZELDA_HUD_BLANK != 0xff 
                && ZELDA_HUD_1 != 0xff
                && ZELDA_HUD_2 != 0xff
                && ZELDA_HUD_3 != 0xff
                && ZELDA_HUD_4 != 0xff
                && ZELDA_HUD_5 != 0xff
                && ZELDA_HUD_6 != 0xff
                && ZELDA_HUD_7 != 0xff
                && ZELDA_HUD_8 != 0xff
                && ZELDA_HUD_9 != 0xff
                && ZELDA_HUD_0 != 0xff
                && ZELDA_HUD_RUPEE != 0xff
                && ZELDA_HUD_HEART_EMPTY != 0xff
                && ZELDA_HUD_HEART_HALF != 0xff
                && ZELDA_HUD_HEART_FULL != 0xff) {
                    found = 1;
                }

            if(ZELDA_HUD_BLANK == 0xff) {
                *ptrBlank = *(UINT8 *)0x9800;
                ZELDA_HUD_BLANK = *ptrBlank;
            }
            if(ZELDA_HUD_1 == 0xff) {
                *ptr1 = *(UINT8 *)0x9801; 
                ZELDA_HUD_1 = *ptr1;
            }
            if(ZELDA_HUD_2 == 0xff) {
                *ptr2 = *(UINT8 *)0x9802; 
                ZELDA_HUD_2 = *ptr2;
            }
            if(ZELDA_HUD_3 == 0xff) {
                *ptr3 = *(UINT8 *)0x9803; 
                ZELDA_HUD_3 = *ptr3;
            }
            if(ZELDA_HUD_4 == 0xff) {
                *ptr4 = *(UINT8 *)0x9804; 
                ZELDA_HUD_4 = *ptr4;
            }
            if(ZELDA_HUD_5 == 0xff) {
                *ptr5 = *(UINT8 *)0x9805; 
                ZELDA_HUD_5 = *ptr5;
            }
            if(ZELDA_HUD_6 == 0xff) {
                *ptr6 = *(UINT8 *)0x9806; 
                ZELDA_HUD_6 = *ptr6;
            }
            if(ZELDA_HUD_7 == 0xff) {
                *ptr7 = *(UINT8 *)0x9807; 
                ZELDA_HUD_7 = *ptr7;
            }
            if(ZELDA_HUD_8 == 0xff) {
                *ptr8 = *(UINT8 *)0x9808; 
                ZELDA_HUD_8 = *ptr8;
            }
            if(ZELDA_HUD_9 == 0xff) {
                *ptr9 = *(UINT8 *)0x9809; 
                ZELDA_HUD_9 = *ptr9;
            }
            if(ZELDA_HUD_0 == 0xff) {
                *ptr0 = *(UINT8 *)0x980a; 
                ZELDA_HUD_0 = *ptr0;
            }
            if(ZELDA_HUD_RUPEE == 0xff) {
                *ptrRupee = *(UINT8 *)0x980b; 
                ZELDA_HUD_RUPEE = *ptrRupee;
            }
            if(ZELDA_HUD_HEART_EMPTY == 0xff) {
                *ptrHeartEmpty = *(UINT8 *)0x980c; 
                ZELDA_HUD_HEART_EMPTY = *ptrHeartEmpty;
            }
            if(ZELDA_HUD_HEART_HALF == 0xff) {
                *ptrHeartHalf = *(UINT8 *)0x980d; 
                ZELDA_HUD_HEART_HALF = *ptrHeartHalf;
            }
            if(ZELDA_HUD_HEART_FULL == 0xff) {
                *ptrHeartFull = *(UINT8 *)0x980e; 
                ZELDA_HUD_HEART_FULL = *ptrHeartFull;
            }
        }        

        hud[0] = ZELDA_HUD_BLANK;
        hud[1] = ZELDA_HUD_HEART_FULL;
        hud[2] = ZELDA_HUD_HEART_HALF;
        hud[3] = ZELDA_HUD_HEART_EMPTY;
        hud[4] = ZELDA_HUD_RUPEE;
        hud[5] = ZELDA_HUD_1;
        hud[6] = ZELDA_HUD_2;
        hud[7] = ZELDA_HUD_3;
        hud[8] = ZELDA_HUD_4;
        hud[9] = ZELDA_HUD_3;
        hud[10] = ZELDA_HUD_5;
        hud[11] = ZELDA_HUD_6;
        hud[12] = ZELDA_HUD_7;
        hud[13] = ZELDA_HUD_8;
        hud[14] = ZELDA_HUD_9;
        hud[15] = ZELDA_HUD_0;
        hud[16] = ZELDA_HUD_RUPEE;
        hud[17] = ZELDA_HUD_HEART_EMPTY;
        hud[18] = ZELDA_HUD_HEART_HALF;
        hud[19] = ZELDA_HUD_HEART_FULL;
        UpdateZeldaHud(1, 1, 1);

        ZELDA_TILES_FOUND = 1;
    } 
}

void SetScene(UINT16 state) {
  state_running = 0;
  next_state = state;
}

void vbl_update() {
  vbl_count++;

  // Update background scroll in vbl
  // interupt to prevent tearing
  SCX_REG = draw_scroll_x;
  SCY_REG = draw_scroll_y;

#ifdef CGB
  if (palette_dirty) {
    set_bkg_palette(0, 8, BkgPaletteBuffer);
    set_sprite_palette(0, 8, SprPaletteBuffer);
    palette_dirty = FALSE;
  }
#endif

  if (music_mute_frames != 0) {
    music_mute_frames--;
    if (music_mute_frames == 0) {
      gbt_enable_channels(0xF);
    }
  }

  if (!hide_sprites) {
    SHOW_SPRITES;
  }
}

void lcd_update() {
  if (LYC_REG == 0x0) {
    if(WY_REG == 0x0) {
      HIDE_SPRITES;
    }

    // If UI is open cause lcd interupt
    // to fire again when first line of
    // window is being drawn
    if (WY_REG != MENU_CLOSED_Y) {
      LYC_REG = WY_REG;
    }
  } else if (WX_REG == WIN_LEFT_X) {
    // If window is covering entire scan line
    // can just hide all sprites until next frame
    HIDE_SPRITES;
    LYC_REG = 0x0;
  } 

  if(IsZeldasAdventureTypeScene()) {
    BYTE heartsChanged = *cachedHealth != *health;
    BYTE maxHeartsChanged = *cachedMaxHearts != *maxHearts;
    BYTE rupeesChanged = *cachedRupees != *rupees;

    if(heartsChanged || maxHeartsChanged || rupeesChanged)
    {
        *cachedHealth = *health;
        *cachedMaxHearts = *maxHearts;
        *cachedRupees = *rupees;
        UpdateZeldaHud(heartsChanged, maxHeartsChanged, rupeesChanged);
    }
  }
}

int core_start() {

#ifdef CGB
  if (_cpu == CGB_TYPE) {
    cpu_fast();
  }
#endif

  display_off();

  // Init LCD
  LCDC_REG = 0x67;

  // Set interupt handlers
  add_VBL(vbl_update);
  add_TIM(MusicUpdate);
  add_LCD(lcd_update);

#ifdef CGB
  TMA_REG = _cpu == CGB_TYPE ? 120U : 0xBCU;
#else
  TMA_REG = 0xBCU;
#endif
  TAC_REG = 0x04U;

  LYC_REG = 0x0;  // LCD interupt pos

  set_interrupts(VBL_IFLAG | TIM_IFLAG | LCD_IFLAG);
  enable_interrupts();

  STAT_REG = 0x45;

  // Set palettes
  BGP_REG = OBP0_REG = 0xE4U;
  OBP1_REG = 0xD2U;

  SCX_REG = 0;
  SCY_REG = 0;

  // Position Window Layer
  WX_REG = 7;
  WY_REG = MAXWNDPOSY + 1U;

  // Initialize structures
  memset(&script_variables, 0, sizeof(script_variables));

  memset(&input_script_ptrs, 0, sizeof(input_script_ptrs));

  memset(&scene_stack, 0, sizeof(scene_stack));
  memset(&script_cmd_args, 0, sizeof(script_cmd_args));
  memset(&script_stack, 0, sizeof(script_stack));
  memset(&script_bank_stack, 0, sizeof(script_bank_stack));
  memset(&script_start_stack, 0, sizeof(script_bank_stack));

  memset(&actors, 0, sizeof(actors));
  memset(&active_script_ctx, 0, sizeof(active_script_ctx));
  memset(&script_ctxs, 0, sizeof(script_ctxs));

  memset(&SprPalette, 0, sizeof(SprPalette));
  memset(&BkgPalette, 0, sizeof(BkgPalette));
  memset(&SprPaletteBuffer, 0, sizeof(SprPaletteBuffer));
  memset(&BkgPaletteBuffer, 0, sizeof(BkgPaletteBuffer));

  // Initialise Player
  player.sprite = 0;
  player.moving = TRUE;
  player.frame = 0;
  player.frames_len = 2;
  map_next_pos.x = start_scene_x;
  map_next_pos.y = start_scene_y;
  map_next_dir.x = player.dir.x = start_scene_dir_x;
  map_next_dir.y = player.dir.y = start_scene_dir_y;
  map_next_sprite = start_player_sprite;
  player.enabled = TRUE;
  player.move_speed = start_player_move_speed;
  player.anim_speed = start_player_anim_speed;

  state_running = 0;
  next_state = start_scene_index;
  game_time = 0;
  scene_type = 0;

  UIInit();
  FadeInit();
  ScriptRunnerInit();
  ActorsInit();

  while (1) {      
    while (state_running) {

      /* Game Core Loop Start *********************************/

      if (!vbl_count) {
        wait_vbl_done();
      }

      delta_time = vbl_count == 1u ? 0u : 1u;
      vbl_count = 0;

      last_joy = joy;
      joy = joypad();
      if ((joy & INPUT_DPAD) != (last_joy & INPUT_DPAD)) {
        recent_joy = joy & ~last_joy;
      }

      if (seedRand) {
      if(seedRand == 2){
        // Seed on first button press
        if (joy) {
          seedRand--;
          initrand((DIV_REG*256)+game_time);
        }
      } else {
        // Seed on first button release
          if (!joy) {
          seedRand = FALSE;
          initrand((DIV_REG*256)+game_time);
        }
      }
    }

      PUSH_BANK(1);

      UpdateCamera();
      RefreshScroll_b();
      UpdateActors();
      UpdateProjectiles_b();
      UIOnInteract_b();
      UIUpdate_b();
 
      if (!script_ctxs[0].script_ptr_bank && !ui_block) {
        PUSH_BANK(stateBanks[scene_type]);
        updateFuncs[scene_type]();
        POP_BANK;
        HandleInputScripts();
      }

      ScriptTimerUpdate();

      ScriptRestoreCtx(0);

      if (!ui_block) {
        // Run background scripts
        ScriptRestoreCtx(1);
        ScriptRestoreCtx(2);
        ScriptRestoreCtx(3);
        ScriptRestoreCtx(4);
        ScriptRestoreCtx(5);
        ScriptRestoreCtx(6);
        ScriptRestoreCtx(7);
        ScriptRestoreCtx(8);
        ScriptRestoreCtx(9);
        ScriptRestoreCtx(10);
        ScriptRestoreCtx(11);

        // Reposition actors and check for collisions
        ActorRunCollisionScripts();
      }

      game_time++;

      POP_BANK;
      
      /* Game Core Loop End ***********************************/
    }


    //  Switch Scene

    // Fade out current scene
    FadeOut();
    while (fade_running) {
      wait_vbl_done();
      FadeUpdate();
    }
    if (!fade_style)
    {
      DISPLAY_OFF
    }

    state_running = 1;
    current_state = next_state;

    // Reset scroll target and camera
    scroll_target = 0;
    scroll_target = &camera_pos;
    camera_settings = CAMERA_LOCK_FLAG;

    // Disable timer script
    timer_script_duration = 0;

    //BGP_REG = PAL_DEF(0U, 1U, 2U, 3U);
    //OBP0_REG = OBP1_REG = PAL_DEF(0U, 0U, 1U, 3U);

    // Force Clear Emote
    move_sprite(0, 0, 0);
    move_sprite(1, 0, 0);
    // Force Clear invoke stack
    script_stack_ptr = 0;
// Force all palettes to update on switch
#ifdef CGB
    palette_update_mask = 0x3F;
#endif

    UIInit();
    LoadScene(current_state);

    // Run scene type init function
    PUSH_BANK(stateBanks[scene_type]);
    startFuncs[scene_type]();  // run start func for new type
    POP_BANK;

    game_time = 0;
    old_scroll_x = scroll_x;
    old_scroll_y = scroll_y;
   
    // Fade in new scene
    DISPLAY_ON;
    FadeIn();

    // Run scene init script
    ScriptStart(&scene_events_start_ptr);
    ScriptRestoreCtx(0);

    UpdateCamera();
    RefreshScroll();
    UpdateActors();
    UIUpdate();   
    
    FindTilesInVram(zeldasAdventureHudMap);
    // UpdateZeldaHud(1, 1, 1);

    // Wait for fade in to complete
    while (fade_running) {
      wait_vbl_done();
      FadeUpdate();
    }
  }  // while(1)
}
