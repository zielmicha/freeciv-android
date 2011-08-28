# client makefile

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := freecivserver
LOCAL_SRC_FILES := common/ai.c common/base.c common/borders.c common/capstr.c common/city.c common/combat.c common/connection.c \
    common/dataio.c common/diptreaty.c common/effects.c common/events.c common/featured_text.c common/game.c common/government.c \
    common/idex.c common/improvement.c common/map.c common/movement.c common/nation.c common/packets.c common/packets_gen.c \
    common/player.c common/requirements.c common/spaceship.c common/specialist.c common/team.c common/tech.c common/terrain.c \
    common/tile.c common/unit.c common/unitlist.c common/unittype.c common/version.c common/vision.c common/worklist.c common/aicore/aisupport.c \
    common/aicore/caravan.c common/aicore/citymap.c common/aicore/cm.c common/aicore/path_finding.c common/aicore/pf_tools.c server/aiiface.c \
    server/auth.c server/barbarian.c server/cityhand.c server/citytools.c server/cityturn.c server/civserver.c server/commands.c \
    server/connecthand.c server/console.c server/diplhand.c server/diplomats.c server/edithand.c server/gamehand.c server/ggzserver.c \
    server/gotohand.c server/handchat.c server/hand_gen.c server/maphand.c server/meta.c server/notify.c server/plrhand.c server/report.c \
    server/ruleset.c server/sanitycheck.c server/savegame.c server/score.c server/sernet.c server/settings.c server/settlers.c server/spacerace.c \
    server/srv_main.c server/stdinhand.c server/techtools.c server/unithand.c server/unittools.c server/voting.c server/generator/height_map.c \
    server/generator/mapgen.c server/generator/mapgen_topology.c server/generator/startpos.c server/generator/temperature_map.c \
    server/generator/utilities.c server/scripting/api_actions.c server/scripting/api_find.c server/scripting/api_gen.c server/scripting/api_intl.c \
    server/scripting/api_methods.c server/scripting/api_notify.c server/scripting/api_utilities.c server/scripting/script.c \
    server/scripting/script_signal.c ai/advdiplomacy.c ai/advdomestic.c ai/advmilitary.c ai/advspace.c ai/aiair.c ai/aicity.c ai/aidata.c \
    ai/aidiplomat.c ai/aiexplorer.c ai/aiferry.c ai/aiguard.c ai/aihand.c ai/aihunt.c ai/ailog.c ai/aiparatrooper.c ai/aisettler.c ai/aitech.c \
    ai/aitools.c ai/aiunit.c utility/astring.c utility/capability.c utility/distribute.c utility/fciconv.c utility/fcintl.c utility/genlist.c \
    utility/hash.c utility/inputfile.c utility/ioz.c utility/iterator.c utility/log.c utility/md5.c utility/mem.c utility/netintf.c utility/pqueue.c \
    utility/rand.c utility/registry.c utility/sbuffer.c utility/shared.c utility/string_vector.c utility/support.c utility/timing.c lua/lapi.c \
    lua/lauxlib.c lua/lbaselib.c lua/lcode.c lua/ldblib.c lua/ldebug.c lua/ldo.c lua/ldump.c lua/lfunc.c lua/lgc.c lua/linit.c lua/liolib.c lua/llex.c \
    lua/lmathlib.c lua/lmem.c lua/loadlib.c lua/lobject.c lua/lopcodes.c lua/loslib.c lua/lparser.c lua/lstate.c lua/lstring.c lua/lstrlib.c lua/ltable.c \
    lua/ltablib.c lua/ltm.c lua/lundump.c lua/lvm.c lua/lzio.c lua/print.c tolua/tolua_event.c tolua/tolua_is.c tolua/tolua_map.c tolua/tolua_push.c \
    tolua/tolua_to.c
LOCAL_CFLAGS    := -Ijni/server -Ijni/server/generator -Ijni/server/scripting -Ijni/common -Ijni/common/aicore -Ijni/utility -Ijni/ai \
    -Ijni/lua -Ijni/tolua -Ijni -DHAVE_CONFIG_H
LOCAL_LDLIBS    := -lz -lm

include $(BUILD_EXECUTABLE)
