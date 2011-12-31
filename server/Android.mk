# server makefile

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := freecivserver
LOCAL_SRC_FILES := tolua/tolua_to.c tolua/tolua_push.c tolua/tolua_map.c tolua/tolua_is.c  \
    tolua/tolua_event.c lua/print.c lua/lzio.c lua/lvm.c lua/lundump.c  \
    lua/ltm.c lua/ltablib.c lua/ltable.c lua/lstrlib.c lua/lstring.c lua/lstate.c  \
    lua/lparser.c lua/loslib.c lua/lopcodes.c lua/lobject.c lua/loadlib.c  \
    lua/lmem.c lua/lmathlib.c lua/llex.c lua/liolib.c lua/linit.c lua/lgc.c  \
    lua/lfunc.c lua/ldump.c lua/ldo.c lua/ldebug.c lua/ldblib.c lua/lcode.c  \
    lua/lbaselib.c lua/lauxlib.c lua/lapi.c utility/timing.c utility/support.c  \
    utility/string_vector.c utility/shared.c utility/registry.c utility/rand.c  \
    utility/pqueue.c utility/netintf.c utility/mem.c utility/md5.c utility/log.c  \
    utility/iterator.c utility/ioz.c utility/inputfile.c utility/genlist.c  \
    utility/genhash.c utility/fc_utf8.c utility/fcintl.c utility/fciconv.c  \
    utility/distribute.c utility/capability.c utility/bitvector.c utility/astring.c  \
    ai/defaultai.c ai/aiunit.c ai/aitools.c ai/aitech.c ai/aisettler.c ai/aiparatrooper.c  \
    ai/aihunt.c ai/aihand.c ai/aiguard.c ai/aiferry.c ai/aidiplomat.c ai/aicity.c  \
    ai/aiair.c ai/advspace.c ai/advmilitary.c ai/advdomestic.c ai/advdiplomacy.c  \
    server/advisors/infracache.c server/advisors/autosettlers.c server/advisors/autoexplorer.c  \
    server/advisors/advtools.c server/advisors/advgoto.c server/advisors/advdata.c  \
    server/advisors/advbuilding.c server/scripting/script_signal.c server/scripting/script.c  \
    server/scripting/api_utilities.c server/scripting/api_specenum.c server/scripting/api_notify.c  \
    server/scripting/api_methods.c server/scripting/api_intl.c server/scripting/api_gen.c  \
    server/scripting/api_find.c server/scripting/api_effects.c server/scripting/api_actions.c  \
    server/generator/utilities.c server/generator/temperature_map.c server/generator/startpos.c  \
    server/generator/mapgen_topology.c server/generator/mapgen.c server/generator/height_map.c  \
    server/voting.c server/unittools.c server/unithand.c server/techtools.c  \
    server/stdinhand.c server/srv_main.c server/srv_log.c server/spacerace.c  \
    server/settings.c server/sernet.c server/score.c server/savegame.c server/savegame2.c  \
    server/sanitycheck.c server/ruleset.c server/report.c server/plrhand.c  \
    server/notify.c server/meta.c server/maphand.c server/hand_gen.c server/handchat.c  \
    server/ggzserver.c server/gamehand.c server/edithand.c server/diplomats.c  \
    server/diplhand.c server/console.c server/connecthand.c server/commands.c  \
    server/civserver.c server/cityturn.c server/citytools.c server/cityhand.c  \
    server/barbarian.c server/auth.c server/aiiface.c common/aicore/pf_tools.c  \
    common/aicore/path_finding.c common/aicore/cm.c common/aicore/citymap.c  \
    common/aicore/caravan.c common/aicore/aisupport.c common/worklist.c common/vision.c  \
    common/version.c common/unittype.c common/unitlist.c common/unit.c common/tile.c  \
    common/terrain.c common/tech.c common/team.c common/specialist.c common/spaceship.c  \
    common/research.c common/requirements.c common/player.c common/packets_gen.c  \
    common/packets.c common/nation.c common/movement.c common/map.c common/improvement.c  \
    common/idex.c common/government.c common/game.c common/featured_text.c  \
    common/fc_interface.c common/events.c common/effects.c common/diptreaty.c  \
    common/dataio.c common/connection.c common/combat.c common/city.c common/capstr.c  \
    common/borders.c common/base.c common/ai.c android_impl.c

LOCAL_CFLAGS    := -Ijni/server -Ijni/server/generator -Ijni/server/advisors -Ijni/server/scripting -Ijni/common -Ijni/common/aicore -Ijni/utility -Ijni/ai \
    -Ijni/lua -Ijni/tolua -Ijni -DHAVE_CONFIG_H
LOCAL_LDLIBS    := -lz -lm

include $(BUILD_EXECUTABLE)
