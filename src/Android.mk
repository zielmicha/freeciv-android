# client makefile

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := freecivclient
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
    utility/registry.c utility/shared.c utility/string_vector.c utility/support.c utility/timing.c
LOCAL_LDLIBS    := -L../.. -L.. -lpython2.7 -lz -lm
LOCAL_CFLAGS    := -Ijni/client -Ijni/client/include -Ijni/client/agents -Ijni/common \
    -Ijni/common/aicore -Ijni/utility -Ijni/python2.7 -Ijni -DHAVE_CONFIG_H

include $(BUILD_SHARED_LIBRARY)