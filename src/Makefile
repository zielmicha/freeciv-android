all: freecivclient.so
objectfiles.a:  objectfiles/ai.o objectfiles/base.o objectfiles/borders.o objectfiles/capstr.o objectfiles/city.o objectfiles/combat.o objectfiles/connection.o objectfiles/dataio.o objectfiles/diptreaty.o objectfiles/effects.o objectfiles/events.o objectfiles/fc_interface.o objectfiles/featured_text.o objectfiles/game.o objectfiles/government.o objectfiles/idex.o objectfiles/improvement.o objectfiles/map.o objectfiles/movement.o objectfiles/nation.o objectfiles/packets.o objectfiles/packets_gen.o objectfiles/player.o objectfiles/requirements.o objectfiles/research.o objectfiles/spaceship.o objectfiles/specialist.o objectfiles/team.o objectfiles/tech.o objectfiles/terrain.o objectfiles/tile.o objectfiles/unit.o objectfiles/unitlist.o objectfiles/unittype.o objectfiles/version.o objectfiles/vision.o objectfiles/worklist.o objectfiles/aisupport.o objectfiles/caravan.o objectfiles/citymap.o objectfiles/cm.o objectfiles/path_finding.o objectfiles/pf_tools.o objectfiles/attribute.o objectfiles/audio.o objectfiles/audio_none.o objectfiles/chatline_common.o objectfiles/citydlg_common.o objectfiles/cityrepdata.o objectfiles/client_main.o objectfiles/climap.o objectfiles/climisc.o objectfiles/clinet.o objectfiles/colors_common.o objectfiles/connectdlg_common.o objectfiles/control.o objectfiles/dummy.o objectfiles/editor.o objectfiles/ggzclient.o objectfiles/global_worklist.o objectfiles/goto.o objectfiles/helpdata.o objectfiles/mapctrl_common.o objectfiles/mapview_common.o objectfiles/messagewin_common.o objectfiles/options.o objectfiles/overview_common.o objectfiles/packhand.o objectfiles/packhand_gen.o objectfiles/plrdlg_common.o objectfiles/repodlgs_common.o objectfiles/reqtree.o objectfiles/servers.o objectfiles/text.o objectfiles/themes_common.o objectfiles/tilespec.o objectfiles/update_queue.o objectfiles/voteinfo.o objectfiles/callauto.o objectfiles/clientauto.o objectfiles/pyclient.o objectfiles/uistub.o objectfiles/agents.o objectfiles/cma_core.o objectfiles/cma_fec.o objectfiles/sha.o objectfiles/astring.o objectfiles/bitvector.o objectfiles/capability.o objectfiles/distribute.o objectfiles/fciconv.o objectfiles/fcintl.o objectfiles/fc_utf8.o objectfiles/genhash.o objectfiles/genlist.o objectfiles/inputfile.o objectfiles/ioz.o objectfiles/iterator.o objectfiles/log.o objectfiles/md5.o objectfiles/mem.o objectfiles/netintf.o objectfiles/pqueue.o objectfiles/rand.o objectfiles/registry.o objectfiles/shared.o objectfiles/string_vector.o objectfiles/support.o objectfiles/timing.o
	ar r objectfiles.a objectfiles/*.o

freecivclient.so: objectfiles.a
	gcc -shared -o freecivclient.so -lm -lz -lpython2.7 objectfiles/*.o
callauto.c: ../callglue
	python ../gencallglue.py

objectfiles/ai.o: common/ai.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/ai.o common/ai.c
objectfiles/base.o: common/base.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/base.o common/base.c
objectfiles/borders.o: common/borders.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/borders.o common/borders.c
objectfiles/capstr.o: common/capstr.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/capstr.o common/capstr.c
objectfiles/city.o: common/city.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/city.o common/city.c
objectfiles/combat.o: common/combat.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/combat.o common/combat.c
objectfiles/connection.o: common/connection.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/connection.o common/connection.c
objectfiles/dataio.o: common/dataio.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/dataio.o common/dataio.c
objectfiles/diptreaty.o: common/diptreaty.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/diptreaty.o common/diptreaty.c
objectfiles/effects.o: common/effects.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/effects.o common/effects.c
objectfiles/events.o: common/events.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/events.o common/events.c
objectfiles/fc_interface.o: common/fc_interface.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/fc_interface.o common/fc_interface.c
objectfiles/featured_text.o: common/featured_text.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/featured_text.o common/featured_text.c
objectfiles/game.o: common/game.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/game.o common/game.c
objectfiles/government.o: common/government.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/government.o common/government.c
objectfiles/idex.o: common/idex.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/idex.o common/idex.c
objectfiles/improvement.o: common/improvement.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/improvement.o common/improvement.c
objectfiles/map.o: common/map.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/map.o common/map.c
objectfiles/movement.o: common/movement.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/movement.o common/movement.c
objectfiles/nation.o: common/nation.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/nation.o common/nation.c
objectfiles/packets.o: common/packets.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/packets.o common/packets.c
objectfiles/packets_gen.o: common/packets_gen.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/packets_gen.o common/packets_gen.c
objectfiles/player.o: common/player.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/player.o common/player.c
objectfiles/requirements.o: common/requirements.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/requirements.o common/requirements.c
objectfiles/research.o: common/research.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/research.o common/research.c
objectfiles/spaceship.o: common/spaceship.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/spaceship.o common/spaceship.c
objectfiles/specialist.o: common/specialist.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/specialist.o common/specialist.c
objectfiles/team.o: common/team.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/team.o common/team.c
objectfiles/tech.o: common/tech.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/tech.o common/tech.c
objectfiles/terrain.o: common/terrain.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/terrain.o common/terrain.c
objectfiles/tile.o: common/tile.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/tile.o common/tile.c
objectfiles/unit.o: common/unit.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/unit.o common/unit.c
objectfiles/unitlist.o: common/unitlist.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/unitlist.o common/unitlist.c
objectfiles/unittype.o: common/unittype.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/unittype.o common/unittype.c
objectfiles/version.o: common/version.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/version.o common/version.c
objectfiles/vision.o: common/vision.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/vision.o common/vision.c
objectfiles/worklist.o: common/worklist.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/worklist.o common/worklist.c
objectfiles/aisupport.o: common/aicore/aisupport.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/aisupport.o common/aicore/aisupport.c
objectfiles/caravan.o: common/aicore/caravan.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/caravan.o common/aicore/caravan.c
objectfiles/citymap.o: common/aicore/citymap.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/citymap.o common/aicore/citymap.c
objectfiles/cm.o: common/aicore/cm.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/cm.o common/aicore/cm.c
objectfiles/path_finding.o: common/aicore/path_finding.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/path_finding.o common/aicore/path_finding.c
objectfiles/pf_tools.o: common/aicore/pf_tools.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/pf_tools.o common/aicore/pf_tools.c
objectfiles/attribute.o: client/attribute.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/attribute.o client/attribute.c
objectfiles/audio.o: client/audio.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/audio.o client/audio.c
objectfiles/audio_none.o: client/audio_none.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/audio_none.o client/audio_none.c
objectfiles/chatline_common.o: client/chatline_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/chatline_common.o client/chatline_common.c
objectfiles/citydlg_common.o: client/citydlg_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/citydlg_common.o client/citydlg_common.c
objectfiles/cityrepdata.o: client/cityrepdata.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/cityrepdata.o client/cityrepdata.c
objectfiles/client_main.o: client/client_main.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/client_main.o client/client_main.c
objectfiles/climap.o: client/climap.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/climap.o client/climap.c
objectfiles/climisc.o: client/climisc.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/climisc.o client/climisc.c
objectfiles/clinet.o: client/clinet.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/clinet.o client/clinet.c
objectfiles/colors_common.o: client/colors_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/colors_common.o client/colors_common.c
objectfiles/connectdlg_common.o: client/connectdlg_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/connectdlg_common.o client/connectdlg_common.c
objectfiles/control.o: client/control.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/control.o client/control.c
objectfiles/dummy.o: client/dummy.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/dummy.o client/dummy.c
objectfiles/editor.o: client/editor.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/editor.o client/editor.c
objectfiles/ggzclient.o: client/ggzclient.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/ggzclient.o client/ggzclient.c
objectfiles/global_worklist.o: client/global_worklist.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/global_worklist.o client/global_worklist.c
objectfiles/goto.o: client/goto.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/goto.o client/goto.c
objectfiles/helpdata.o: client/helpdata.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/helpdata.o client/helpdata.c
objectfiles/mapctrl_common.o: client/mapctrl_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/mapctrl_common.o client/mapctrl_common.c
objectfiles/mapview_common.o: client/mapview_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/mapview_common.o client/mapview_common.c
objectfiles/messagewin_common.o: client/messagewin_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/messagewin_common.o client/messagewin_common.c
objectfiles/options.o: client/options.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/options.o client/options.c
objectfiles/overview_common.o: client/overview_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/overview_common.o client/overview_common.c
objectfiles/packhand.o: client/packhand.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/packhand.o client/packhand.c
objectfiles/packhand_gen.o: client/packhand_gen.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/packhand_gen.o client/packhand_gen.c
objectfiles/plrdlg_common.o: client/plrdlg_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/plrdlg_common.o client/plrdlg_common.c
objectfiles/repodlgs_common.o: client/repodlgs_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/repodlgs_common.o client/repodlgs_common.c
objectfiles/reqtree.o: client/reqtree.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/reqtree.o client/reqtree.c
objectfiles/servers.o: client/servers.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/servers.o client/servers.c
objectfiles/text.o: client/text.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/text.o client/text.c
objectfiles/themes_common.o: client/themes_common.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/themes_common.o client/themes_common.c
objectfiles/tilespec.o: client/tilespec.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/tilespec.o client/tilespec.c
objectfiles/update_queue.o: client/update_queue.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/update_queue.o client/update_queue.c
objectfiles/voteinfo.o: client/voteinfo.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/voteinfo.o client/voteinfo.c
objectfiles/callauto.o: callauto.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/callauto.o callauto.c
objectfiles/clientauto.o: clientauto.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/clientauto.o clientauto.c
objectfiles/pyclient.o: pyclient.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/pyclient.o pyclient.c
objectfiles/uistub.o: uistub.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/uistub.o uistub.c
objectfiles/agents.o: client/agents/agents.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/agents.o client/agents/agents.c
objectfiles/cma_core.o: client/agents/cma_core.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/cma_core.o client/agents/cma_core.c
objectfiles/cma_fec.o: client/agents/cma_fec.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/cma_fec.o client/agents/cma_fec.c
objectfiles/sha.o: client/agents/sha.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/sha.o client/agents/sha.c
objectfiles/astring.o: utility/astring.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/astring.o utility/astring.c
objectfiles/bitvector.o: utility/bitvector.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/bitvector.o utility/bitvector.c
objectfiles/capability.o: utility/capability.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/capability.o utility/capability.c
objectfiles/distribute.o: utility/distribute.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/distribute.o utility/distribute.c
objectfiles/fciconv.o: utility/fciconv.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/fciconv.o utility/fciconv.c
objectfiles/fcintl.o: utility/fcintl.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/fcintl.o utility/fcintl.c
objectfiles/fc_utf8.o: utility/fc_utf8.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/fc_utf8.o utility/fc_utf8.c
objectfiles/genhash.o: utility/genhash.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/genhash.o utility/genhash.c
objectfiles/genlist.o: utility/genlist.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/genlist.o utility/genlist.c
objectfiles/inputfile.o: utility/inputfile.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/inputfile.o utility/inputfile.c
objectfiles/ioz.o: utility/ioz.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/ioz.o utility/ioz.c
objectfiles/iterator.o: utility/iterator.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/iterator.o utility/iterator.c
objectfiles/log.o: utility/log.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/log.o utility/log.c
objectfiles/md5.o: utility/md5.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/md5.o utility/md5.c
objectfiles/mem.o: utility/mem.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/mem.o utility/mem.c
objectfiles/netintf.o: utility/netintf.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/netintf.o utility/netintf.c
objectfiles/pqueue.o: utility/pqueue.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/pqueue.o utility/pqueue.c
objectfiles/rand.o: utility/rand.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/rand.o utility/rand.c
objectfiles/registry.o: utility/registry.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/registry.o utility/registry.c
objectfiles/shared.o: utility/shared.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/shared.o utility/shared.c
objectfiles/string_vector.o: utility/string_vector.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/string_vector.o utility/string_vector.c
objectfiles/support.o: utility/support.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/support.o utility/support.c
objectfiles/timing.o: utility/timing.c
	gcc -g -Iclient -Iclient/include -Iclient/agents -Icommon -Icommon/aicore -Iutility -Ipython2.7 -I. -DHAVE_CONFIG_H  -c -o objectfiles/timing.o utility/timing.c
