export const SET_TOOL = "SET_TOOL";
export const SET_SECTION = "SET_SECTION";
export const SET_NAVIGATION_ID = "SET_NAVIGATION_ID";

export const PROJECT_LOAD_REQUEST = "PROJECT_LOAD_REQUEST";
export const PROJECT_LOAD_SUCCESS = "PROJECT_LOAD_SUCCESS";
export const PROJECT_LOAD_FAILURE = "PROJECT_LOAD_FAILURE";

export const SPRITE_LOAD_REQUEST = "SPRITE_LOAD_REQUEST";
export const SPRITE_LOAD_SUCCESS = "SPRITE_LOAD_SUCCESS";
export const SPRITE_LOAD_FAILURE = "SPRITE_LOAD_FAILURE";
export const SPRITE_REMOVE = "SPRITE_REMOVE";

export const BACKGROUND_LOAD_REQUEST = "BACKGROUND_LOAD_REQUEST";
export const BACKGROUND_LOAD_SUCCESS = "BACKGROUND_LOAD_SUCCESS";
export const BACKGROUND_LOAD_FAILURE = "BACKGROUND_LOAD_FAILURE";
export const BACKGROUND_REMOVE = "BACKGROUND_REMOVE";

export const MUSIC_LOAD_REQUEST = "MUSIC_LOAD_REQUEST";
export const MUSIC_LOAD_SUCCESS = "MUSIC_LOAD_SUCCESS";
export const MUSIC_LOAD_FAILURE = "MUSIC_LOAD_FAILURE";
export const MUSIC_REMOVE = "MUSIC_REMOVE";

export const PROJECT_SAVE_REQUEST = "PROJECT_SAVE_REQUEST";
export const PROJECT_SAVE_SUCCESS = "PROJECT_SAVE_SUCCESS";
export const PROJECT_SAVE_FAILURE = "PROJECT_SAVE_FAILURE";

export const PROJECT_SAVE_AS_REQUEST = "PROJECT_SAVE_AS_REQUEST";
export const PROJECT_SAVE_AS_SUCCESS = "PROJECT_SAVE_AS_SUCCESS";
export const PROJECT_SAVE_AS_FAILURE = "PROJECT_SAVE_AS_FAILURE";

export const RELOAD_ASSETS = "RELOAD_ASSETS";

export const ADD_SCENE = "ADD_SCENE";
export const MOVE_SCENE = "MOVE_SCENE";
export const EDIT_SCENE = "EDIT_SCENE";
export const REMOVE_SCENE = "REMOVE_SCENE";
export const SELECT_SCENE = "SELECT_SCENE";
export const DRAG_SCENE = "DRAG_SCENE";
export const DRAG_SCENE_START = "DRAG_SCENE_START";
export const DRAG_SCENE_STOP = "DRAG_SCENE_STOP";

export const DRAG_PLAYER_START = "DRAG_PLAYER_START";
export const DRAG_PLAYER_STOP = "DRAG_PLAYER_STOP";
export const DRAG_DESTINATION_START = "DRAG_DESTINATION_START";
export const DRAG_DESTINATION_STOP = "DRAG_DESTINATION_STOP";
export const DRAG_ACTOR_START = "DRAG_ACTOR_START";
export const DRAG_ACTOR_STOP = "DRAG_ACTOR_STOP";
export const DRAG_TRIGGER_START = "DRAG_TRIGGER_START";
export const DRAG_TRIGGER_STOP = "DRAG_TRIGGER_STOP";

export const SCENE_HOVER = "SCENE_HOVER";
export const ACTOR_HOVER = "ACTOR_HOVER";

export const SIDEBAR_WORLD_RESIZE = "SIDEBAR_WORLD_RESIZE";
export const SIDEBAR_FILES_RESIZE = "SIDEBAR_FILES_RESIZE";

export const EDIT_SCENE_EVENT_DESTINATION_POSITION =
  "EDIT_SCENE_EVENT_DESTINATION_POSITION";
export const EDIT_ACTOR_EVENT_DESTINATION_POSITION =
  "EDIT_ACTOR_EVENT_DESTINATION_POSITION";
export const EDIT_TRIGGER_EVENT_DESTINATION_POSITION =
  "EDIT_TRIGGER_EVENT_DESTINATION_POSITION";

export const ADD_ACTOR = "ADD_ACTOR";
export const MOVE_ACTOR = "MOVE_ACTOR";
export const REMOVE_ACTOR = "REMOVE_ACTOR";
export const REMOVE_ACTOR_AT = "REMOVE_ACTOR_AT";
export const SELECT_ACTOR = "SELECT_ACTOR";
export const EDIT_ACTOR = "EDIT_ACTOR";
export const SELECT_SCRIPT_EVENT = "SELECT_SCRIPT_EVENT";

export const ADD_TRIGGER = "CREATE_TRIGGER";
export const RESIZE_TRIGGER = "RESIZE_TRIGGER";
export const MOVE_TRIGGER = "MOVE_TRIGGER";
export const REMOVE_TRIGGER = "REMOVE_TRIGGER";
export const REMOVE_TRIGGER_AT = "REMOVE_TRIGGER_AT";
export const EDIT_TRIGGER = "EDIT_TRIGGER";
export const SELECT_TRIGGER = "SELECT_TRIGGER";

export const PAINT_COLLISION_TILE = "PAINT_COLLISION_TILE";
export const PAINT_COLLISION_LINE = "PAINT_COLLISION_LINE";
export const PAINT_COLLISION_FILL = "PAINT_COLLISION_FILL";

export const PAINT_COLOR_TILE = "PAINT_COLOR_TILE";
export const PAINT_COLOR_LINE = "PAINT_COLOR_LINE";
export const PAINT_COLOR_FILL = "PAINT_COLOR_FILL";

export const SET_SHOW_LAYERS = "SET_SHOW_LAYERS";

export const RENAME_VARIABLE = "RENAME_VARIABLE";

export const ADD_PALETTE = "ADD_PALETTE";
export const EDIT_PALETTE = "EDIT_PALETTE";
export const REMOVE_PALETTE = "REMOVE_PALETTE";

export const SET_SELECTED_BRUSH = "SET_SELECTED_BRUSH";
export const SET_SELECTED_PALETTE = "SET_SELECTED_PALETTE";
export const SET_SELECTED_TILE_TYPE = "SET_SELECTED_TILE_TYPE";

export const SET_STATUS = "SET_STATUS";

export const SELECT_WORLD = "SELECT_WORLD";
export const EDIT_WORLD = "EDIT_WORLD";

export const SELECT_SIDEBAR = "SELECT_SIDEBAR";

export const ADD_CUSTOM_EVENT = "ADD_CUSTOM_EVENT";
export const EDIT_CUSTOM_EVENT = "EDIT_CUSTOM_EVENT";
export const REMOVE_CUSTOM_EVENT = "REMOVE_CUSTOM_EVENT";
export const SELECT_CUSTOM_EVENT = "SELECT_CUSTOM_EVENT";

export const EDIT_PROJECT = "EDIT_PROJECT";
export const EDIT_PROJECT_SETTINGS = "EDIT_PROJECT_SETTINGS";
export const EDIT_PLAYER_START_AT = "EDIT_PLAYER_START_AT";

export const SCROLL_WORLD = "SCROLL_WORLD";
export const SCROLL_WORLD_THROTTLED = "SCROLL_WORLD_THROTTLED";
export const RESIZE_WORLD_VIEW = "RESIZE_WORLD_VIEW";
export const EDIT_SEARCH_TERM = "EDIT_SEARCH_TERM";

export const OPEN_HELP = "OPEN_HELP";
export const OPEN_FOLDER = "OPEN_FOLDER";
export const BUILD_GAME = "BUILD_GAME";
export const DELETE_BUILD_CACHE = "DELETE_BUILD_CACHE";
export const SET_PROFILING = "SET_PROFILING";

export const EJECT_ENGINE = "EJECT_ENGINE";

export const PLAY_SOUNDFX_BEEP = "PLAY_SOUNDFX_BEEP";
export const PLAY_SOUNDFX_TONE = "PLAY_SOUNDFX_TONE";
export const PLAY_SOUNDFX_CRASH = "PLAY_SOUNDFX_CRASH";
export const PAUSE_SOUNDFX = "PAUSE_SOUNDFX";

export const EDIT_UI = "EDIT_UI";

export const COPY_EVENT = "COPY_EVENT";
export const COPY_SCRIPT = "COPY_SCRIPT";
export const COPY_ACTOR = "COPY_ACTOR";
export const COPY_TRIGGER = "COPY_TRIGGER";
export const COPY_SCENE = "COPY_SCENE";

export const PASTE_ACTOR = "PASTE_ACTOR";
export const PASTE_TRIGGER = "PASTE_TRIGGER";
export const PASTE_SCENE = "PASTE_SCENE";
export const PASTE_CUSTOM_EVENTS = "PASTE_CUSTOM_EVENTS";

export const SET_ACTOR_PREFAB = "SET_ACTOR_PREFAB";
export const SET_TRIGGER_PREFAB = "SET_TRIGGER_PREFAB";
export const SET_SCENE_PREFAB = "SET_SCENE_PREFAB";

export const SET_GLOBAL_ERROR = "SET_GLOBAL_ERROR";

export const SET_SCRIPT_TAB = "SET_SCRIPT_TAB";
export const SET_SCRIPT_TAB_SCENE = "SET_SCRIPT_TAB_SCENE";
export const SET_SCRIPT_TAB_SECONDARY = "SET_SCRIPT_TAB_SECONDARY";

export const CHECK_BACKGROUND_WARNINGS = "CHECK_BACKGROUND_WARNINGS";
export const CHECK_SPRITE_WARNINGS = "CHECK_SPRITE_WARNINGS";
export const SET_BACKGROUND_WARNINGS = "SET_BACKGROUND_WARNINGS";
export const SET_SPRITE_WARNINGS = "SET_SPRITE_WARNINGS";
