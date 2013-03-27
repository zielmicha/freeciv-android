# client makefile

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := freeciv
LOCAL_SRC_FILES := common/ai.c common/base.c common/borders.c common/capstr.c common/city.c \
    common/combat.c common/connection.c common/dataio.c common/diptreaty.c common/effects.c \
    common/events.c common/fc_interface.c common/featured_text.c common/game.c common/government.c \
    common/idex.c common/improvement.c common/map.c common/movement.c common/nation.c common/packets.c \
    common/packets_gen.c common/player.c common/requirements.c common/research.c common/spaceship.c \
    common/specialist.c common/team.c common/tech.c common/terrain.c common/tile.c common/unit.c \
    common/unitlist.c common/unittype.c common/version.c common/vision.c common/worklist.c \
    common/aicore/aisupport.c common/aicore/caravan.c common/aicore/citymap.c common/aicore/cm.c \
    common/aicore/path_finding.c common/aicore/pf_tools.c client/attribute.c client/audio.c \
    client/audio_none.c client/chatline_common.c client/citydlg_common.c \
    client/cityrepdata.c client/client_main.c client/climap.c client/climisc.c client/clinet.c \
    client/colors_common.c client/connectdlg_common.c client/control.c client/dummy.c \
    client/editor.c client/ggzclient.c client/global_worklist.c client/goto.c client/helpdata.c \
    client/mapctrl_common.c client/mapview_common.c client/messagewin_common.c client/options.c \
    client/overview_common.c client/packhand.c client/packhand_gen.c client/plrdlg_common.c \
    client/repodlgs_common.c client/reqtree.c client/servers.c client/text.c client/themes_common.c \
    client/tilespec.c client/update_queue.c client/voteinfo.c callauto.c clientauto.c \
    pyclient.c uistub.c client/agents/agents.c client/agents/cma_core.c client/agents/cma_fec.c \
    client/agents/sha.c utility/astring.c utility/bitvector.c utility/capability.c  \
    utility/distribute.c utility/fciconv.c utility/fcintl.c utility/fc_utf8.c utility/genhash.c \
    utility/genlist.c utility/inputfile.c utility/ioz.c utility/iterator.c utility/log.c \
    utility/md5.c utility/mem.c utility/netintf.c utility/pqueue.c utility/rand.c \
    utility/registry.c utility/shared.c utility/string_vector.c utility/support.c utility/timing.c \
	server/aiiface.c server/auth.c server/barbarian.c server/cityhand.c server/citytools.c server/cityturn.c \
	server/civserver.c server/commands.c server/connecthand.c server/console.c server/diplhand.c \
	server/diplomats.c server/edithand.c server/gamehand.c server/ggzserver.c server/handchat.c \
	server/hand_gen.c server/maphand.c server/meta.c server/notify.c server/plrhand.c server/report.c \
	server/ruleset.c server/sanitycheck.c server/savegame2.c server/savegame.c server/score.c server/sernet.c \
	server/settings.c server/spacerace.c server/srv_log.c server/srv_main.c server/stdinhand.c server/techtools.c \
	server/unithand.c server/unittools.c server/voting.c \
	server/advisors/advbuilding.c server/advisors/advdata.c server/advisors/advgoto.c server/advisors/advtools.c \
	server/advisors/autoexplorer.c server/advisors/autosettlers.c server/advisors/infracache.c \
	server/generator/height_map.c server/generator/mapgen.c server/generator/mapgen_topology.c \
	server/generator/startpos.c server/generator/temperature_map.c server/generator/utilities.c \
	server/scripting/api_actions.c server/scripting/api_effects.c server/scripting/api_find.c \
	server/scripting/api_gen.c server/scripting/api_intl.c server/scripting/api_methods.c server/scripting/api_notify.c \
	server/scripting/api_specenum.c server/scripting/api_utilities.c server/scripting/script.c server/scripting/script_signal.c \
	ai/advdiplomacy.c ai/advdomestic.c ai/advmilitary.c ai/advspace.c ai/aiair.c ai/aicity.c ai/aidiplomat.c ai/aiferry.c \
	ai/aiguard.c ai/aihand.c ai/aihunt.c ai/aiparatrooper.c ai/aisettler.c ai/aitech.c ai/aitools.c ai/aiunit.c ai/defaultai.c \
	tolua/tolua_event.c tolua/tolua_is.c tolua/tolua_map.c tolua/tolua_push.c tolua/tolua_to.c lua/lapi.c \
	lua/lauxlib.c lua/lbaselib.c lua/lcode.c lua/ldblib.c lua/ldebug.c lua/ldo.c lua/ldump.c lua/lfunc.c lua/lgc.c \
	lua/linit.c lua/liolib.c lua/llex.c lua/lmathlib.c lua/lmem.c lua/loadlib.c lua/lobject.c lua/lopcodes.c lua/loslib.c \
	lua/lparser.c lua/lstate.c lua/lstring.c lua/lstrlib.c lua/ltable.c lua/ltablib.c lua/ltm.c lua/lundump.c lua/lvm.c \
	lua/lzio.c lua/print.c android_server_impl.c

LOCAL_LDLIBS    := -lz -lm
LOCAL_SHARED_LIBRARIES := python2.7
LOCAL_C_INCLUDES    := $(LOCAL_PATH)/client $(LOCAL_PATH)/client/include $(LOCAL_PATH)/client/agents $(LOCAL_PATH)/common $(LOCAL_PATH)/ai $(LOCAL_PATH)/common/aicore $(LOCAL_PATH)/utility $(LOCAL_PATH)/server $(LOCAL_PATH)/server/advisors $(LOCAL_PATH)/server/generator $(LOCAL_PATH)/server/scripting $(LOCAL_PATH)/lua $(LOCAL_PATH)/tolua $(LOCAL_PATH) jni/python/Include jni/python
LOCAL_CFLAGS	:= -DHAVE_CONFIG_H

include $(BUILD_SHARED_LIBRARY)
