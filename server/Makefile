all: freeciv-server
objectfiles.a:  objectfiles/ai.o objectfiles/base.o objectfiles/borders.o objectfiles/capstr.o objectfiles/city.o objectfiles/combat.o objectfiles/connection.o objectfiles/dataio.o objectfiles/diptreaty.o objectfiles/effects.o objectfiles/events.o objectfiles/featured_text.o objectfiles/game.o objectfiles/government.o objectfiles/idex.o objectfiles/improvement.o objectfiles/map.o objectfiles/movement.o objectfiles/nation.o objectfiles/packets.o objectfiles/packets_gen.o objectfiles/player.o objectfiles/requirements.o objectfiles/spaceship.o objectfiles/specialist.o objectfiles/team.o objectfiles/tech.o objectfiles/terrain.o objectfiles/tile.o objectfiles/unit.o objectfiles/unitlist.o objectfiles/unittype.o objectfiles/version.o objectfiles/vision.o objectfiles/worklist.o objectfiles/aisupport.o objectfiles/caravan.o objectfiles/citymap.o objectfiles/cm.o objectfiles/path_finding.o objectfiles/pf_tools.o objectfiles/aiiface.o objectfiles/auth.o objectfiles/barbarian.o objectfiles/cityhand.o objectfiles/citytools.o objectfiles/cityturn.o objectfiles/civserver.o objectfiles/commands.o objectfiles/connecthand.o objectfiles/console.o objectfiles/diplhand.o objectfiles/diplomats.o objectfiles/edithand.o objectfiles/gamehand.o objectfiles/ggzserver.o objectfiles/gotohand.o objectfiles/handchat.o objectfiles/hand_gen.o objectfiles/maphand.o objectfiles/meta.o objectfiles/notify.o objectfiles/plrhand.o objectfiles/report.o objectfiles/ruleset.o objectfiles/sanitycheck.o objectfiles/savegame.o objectfiles/score.o objectfiles/sernet.o objectfiles/settings.o objectfiles/settlers.o objectfiles/spacerace.o objectfiles/srv_main.o objectfiles/stdinhand.o objectfiles/techtools.o objectfiles/unithand.o objectfiles/unittools.o objectfiles/voting.o objectfiles/height_map.o objectfiles/mapgen.o objectfiles/mapgen_topology.o objectfiles/startpos.o objectfiles/temperature_map.o objectfiles/utilities.o objectfiles/api_actions.o objectfiles/api_find.o objectfiles/api_gen.o objectfiles/api_intl.o objectfiles/api_methods.o objectfiles/api_notify.o objectfiles/api_utilities.o objectfiles/script.o objectfiles/script_signal.o objectfiles/advdiplomacy.o objectfiles/advdomestic.o objectfiles/advmilitary.o objectfiles/advspace.o objectfiles/aiair.o objectfiles/aicity.o objectfiles/aidata.o objectfiles/aidiplomat.o objectfiles/aiexplorer.o objectfiles/aiferry.o objectfiles/aiguard.o objectfiles/aihand.o objectfiles/aihunt.o objectfiles/ailog.o objectfiles/aiparatrooper.o objectfiles/aisettler.o objectfiles/aitech.o objectfiles/aitools.o objectfiles/aiunit.o objectfiles/astring.o objectfiles/capability.o objectfiles/distribute.o objectfiles/fciconv.o objectfiles/fcintl.o objectfiles/genlist.o objectfiles/hash.o objectfiles/inputfile.o objectfiles/ioz.o objectfiles/iterator.o objectfiles/log.o objectfiles/md5.o objectfiles/mem.o objectfiles/netintf.o objectfiles/pqueue.o objectfiles/rand.o objectfiles/registry.o objectfiles/sbuffer.o objectfiles/shared.o objectfiles/string_vector.o objectfiles/support.o objectfiles/timing.o objectfiles/lapi.o objectfiles/lauxlib.o objectfiles/lbaselib.o objectfiles/lcode.o objectfiles/ldblib.o objectfiles/ldebug.o objectfiles/ldo.o objectfiles/ldump.o objectfiles/lfunc.o objectfiles/lgc.o objectfiles/linit.o objectfiles/liolib.o objectfiles/llex.o objectfiles/lmathlib.o objectfiles/lmem.o objectfiles/loadlib.o objectfiles/lobject.o objectfiles/lopcodes.o objectfiles/loslib.o objectfiles/lparser.o objectfiles/lstate.o objectfiles/lstring.o objectfiles/lstrlib.o objectfiles/ltable.o objectfiles/ltablib.o objectfiles/ltm.o objectfiles/lundump.o objectfiles/lvm.o objectfiles/lzio.o objectfiles/print.o objectfiles/tolua_event.o objectfiles/tolua_is.o objectfiles/tolua_map.o objectfiles/tolua_push.o objectfiles/tolua_to.o
	ar r objectfiles.a objectfiles/*.o
freeciv-server: objectfiles.a
	gcc -o freeciv-server -lm -lz objectfiles/*.o

objectfiles/ai.o: common/ai.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ai.o common/ai.c
objectfiles/base.o: common/base.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/base.o common/base.c
objectfiles/borders.o: common/borders.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/borders.o common/borders.c
objectfiles/capstr.o: common/capstr.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/capstr.o common/capstr.c
objectfiles/city.o: common/city.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/city.o common/city.c
objectfiles/combat.o: common/combat.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/combat.o common/combat.c
objectfiles/connection.o: common/connection.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/connection.o common/connection.c
objectfiles/dataio.o: common/dataio.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/dataio.o common/dataio.c
objectfiles/diptreaty.o: common/diptreaty.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/diptreaty.o common/diptreaty.c
objectfiles/effects.o: common/effects.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/effects.o common/effects.c
objectfiles/events.o: common/events.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/events.o common/events.c
objectfiles/featured_text.o: common/featured_text.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/featured_text.o common/featured_text.c
objectfiles/game.o: common/game.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/game.o common/game.c
objectfiles/government.o: common/government.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/government.o common/government.c
objectfiles/idex.o: common/idex.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/idex.o common/idex.c
objectfiles/improvement.o: common/improvement.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/improvement.o common/improvement.c
objectfiles/map.o: common/map.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/map.o common/map.c
objectfiles/movement.o: common/movement.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/movement.o common/movement.c
objectfiles/nation.o: common/nation.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/nation.o common/nation.c
objectfiles/packets.o: common/packets.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/packets.o common/packets.c
objectfiles/packets_gen.o: common/packets_gen.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/packets_gen.o common/packets_gen.c
objectfiles/player.o: common/player.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/player.o common/player.c
objectfiles/requirements.o: common/requirements.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/requirements.o common/requirements.c
objectfiles/spaceship.o: common/spaceship.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/spaceship.o common/spaceship.c
objectfiles/specialist.o: common/specialist.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/specialist.o common/specialist.c
objectfiles/team.o: common/team.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/team.o common/team.c
objectfiles/tech.o: common/tech.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/tech.o common/tech.c
objectfiles/terrain.o: common/terrain.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/terrain.o common/terrain.c
objectfiles/tile.o: common/tile.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/tile.o common/tile.c
objectfiles/unit.o: common/unit.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/unit.o common/unit.c
objectfiles/unitlist.o: common/unitlist.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/unitlist.o common/unitlist.c
objectfiles/unittype.o: common/unittype.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/unittype.o common/unittype.c
objectfiles/version.o: common/version.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/version.o common/version.c
objectfiles/vision.o: common/vision.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/vision.o common/vision.c
objectfiles/worklist.o: common/worklist.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/worklist.o common/worklist.c
objectfiles/aisupport.o: common/aicore/aisupport.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aisupport.o common/aicore/aisupport.c
objectfiles/caravan.o: common/aicore/caravan.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/caravan.o common/aicore/caravan.c
objectfiles/citymap.o: common/aicore/citymap.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/citymap.o common/aicore/citymap.c
objectfiles/cm.o: common/aicore/cm.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/cm.o common/aicore/cm.c
objectfiles/path_finding.o: common/aicore/path_finding.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/path_finding.o common/aicore/path_finding.c
objectfiles/pf_tools.o: common/aicore/pf_tools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/pf_tools.o common/aicore/pf_tools.c
objectfiles/aiiface.o: server/aiiface.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aiiface.o server/aiiface.c
objectfiles/auth.o: server/auth.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/auth.o server/auth.c
objectfiles/barbarian.o: server/barbarian.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/barbarian.o server/barbarian.c
objectfiles/cityhand.o: server/cityhand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/cityhand.o server/cityhand.c
objectfiles/citytools.o: server/citytools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/citytools.o server/citytools.c
objectfiles/cityturn.o: server/cityturn.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/cityturn.o server/cityturn.c
objectfiles/civserver.o: server/civserver.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/civserver.o server/civserver.c
objectfiles/commands.o: server/commands.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/commands.o server/commands.c
objectfiles/connecthand.o: server/connecthand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/connecthand.o server/connecthand.c
objectfiles/console.o: server/console.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/console.o server/console.c
objectfiles/diplhand.o: server/diplhand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/diplhand.o server/diplhand.c
objectfiles/diplomats.o: server/diplomats.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/diplomats.o server/diplomats.c
objectfiles/edithand.o: server/edithand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/edithand.o server/edithand.c
objectfiles/gamehand.o: server/gamehand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/gamehand.o server/gamehand.c
objectfiles/ggzserver.o: server/ggzserver.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ggzserver.o server/ggzserver.c
objectfiles/gotohand.o: server/gotohand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/gotohand.o server/gotohand.c
objectfiles/handchat.o: server/handchat.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/handchat.o server/handchat.c
objectfiles/hand_gen.o: server/hand_gen.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/hand_gen.o server/hand_gen.c
objectfiles/maphand.o: server/maphand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/maphand.o server/maphand.c
objectfiles/meta.o: server/meta.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/meta.o server/meta.c
objectfiles/notify.o: server/notify.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/notify.o server/notify.c
objectfiles/plrhand.o: server/plrhand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/plrhand.o server/plrhand.c
objectfiles/report.o: server/report.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/report.o server/report.c
objectfiles/ruleset.o: server/ruleset.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ruleset.o server/ruleset.c
objectfiles/sanitycheck.o: server/sanitycheck.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/sanitycheck.o server/sanitycheck.c
objectfiles/savegame.o: server/savegame.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/savegame.o server/savegame.c
objectfiles/score.o: server/score.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/score.o server/score.c
objectfiles/sernet.o: server/sernet.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/sernet.o server/sernet.c
objectfiles/settings.o: server/settings.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/settings.o server/settings.c
objectfiles/settlers.o: server/settlers.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/settlers.o server/settlers.c
objectfiles/spacerace.o: server/spacerace.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/spacerace.o server/spacerace.c
objectfiles/srv_main.o: server/srv_main.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/srv_main.o server/srv_main.c
objectfiles/stdinhand.o: server/stdinhand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/stdinhand.o server/stdinhand.c
objectfiles/techtools.o: server/techtools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/techtools.o server/techtools.c
objectfiles/unithand.o: server/unithand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/unithand.o server/unithand.c
objectfiles/unittools.o: server/unittools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/unittools.o server/unittools.c
objectfiles/voting.o: server/voting.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/voting.o server/voting.c
objectfiles/height_map.o: server/generator/height_map.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/height_map.o server/generator/height_map.c
objectfiles/mapgen.o: server/generator/mapgen.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/mapgen.o server/generator/mapgen.c
objectfiles/mapgen_topology.o: server/generator/mapgen_topology.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/mapgen_topology.o server/generator/mapgen_topology.c
objectfiles/startpos.o: server/generator/startpos.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/startpos.o server/generator/startpos.c
objectfiles/temperature_map.o: server/generator/temperature_map.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/temperature_map.o server/generator/temperature_map.c
objectfiles/utilities.o: server/generator/utilities.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/utilities.o server/generator/utilities.c
objectfiles/api_actions.o: server/scripting/api_actions.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/api_actions.o server/scripting/api_actions.c
objectfiles/api_find.o: server/scripting/api_find.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/api_find.o server/scripting/api_find.c
objectfiles/api_gen.o: server/scripting/api_gen.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/api_gen.o server/scripting/api_gen.c
objectfiles/api_intl.o: server/scripting/api_intl.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/api_intl.o server/scripting/api_intl.c
objectfiles/api_methods.o: server/scripting/api_methods.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/api_methods.o server/scripting/api_methods.c
objectfiles/api_notify.o: server/scripting/api_notify.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/api_notify.o server/scripting/api_notify.c
objectfiles/api_utilities.o: server/scripting/api_utilities.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/api_utilities.o server/scripting/api_utilities.c
objectfiles/script.o: server/scripting/script.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/script.o server/scripting/script.c
objectfiles/script_signal.o: server/scripting/script_signal.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/script_signal.o server/scripting/script_signal.c
objectfiles/advdiplomacy.o: ai/advdiplomacy.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/advdiplomacy.o ai/advdiplomacy.c
objectfiles/advdomestic.o: ai/advdomestic.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/advdomestic.o ai/advdomestic.c
objectfiles/advmilitary.o: ai/advmilitary.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/advmilitary.o ai/advmilitary.c
objectfiles/advspace.o: ai/advspace.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/advspace.o ai/advspace.c
objectfiles/aiair.o: ai/aiair.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aiair.o ai/aiair.c
objectfiles/aicity.o: ai/aicity.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aicity.o ai/aicity.c
objectfiles/aidata.o: ai/aidata.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aidata.o ai/aidata.c
objectfiles/aidiplomat.o: ai/aidiplomat.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aidiplomat.o ai/aidiplomat.c
objectfiles/aiexplorer.o: ai/aiexplorer.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aiexplorer.o ai/aiexplorer.c
objectfiles/aiferry.o: ai/aiferry.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aiferry.o ai/aiferry.c
objectfiles/aiguard.o: ai/aiguard.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aiguard.o ai/aiguard.c
objectfiles/aihand.o: ai/aihand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aihand.o ai/aihand.c
objectfiles/aihunt.o: ai/aihunt.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aihunt.o ai/aihunt.c
objectfiles/ailog.o: ai/ailog.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ailog.o ai/ailog.c
objectfiles/aiparatrooper.o: ai/aiparatrooper.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aiparatrooper.o ai/aiparatrooper.c
objectfiles/aisettler.o: ai/aisettler.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aisettler.o ai/aisettler.c
objectfiles/aitech.o: ai/aitech.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aitech.o ai/aitech.c
objectfiles/aitools.o: ai/aitools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aitools.o ai/aitools.c
objectfiles/aiunit.o: ai/aiunit.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/aiunit.o ai/aiunit.c
objectfiles/astring.o: utility/astring.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/astring.o utility/astring.c
objectfiles/capability.o: utility/capability.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/capability.o utility/capability.c
objectfiles/distribute.o: utility/distribute.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/distribute.o utility/distribute.c
objectfiles/fciconv.o: utility/fciconv.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/fciconv.o utility/fciconv.c
objectfiles/fcintl.o: utility/fcintl.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/fcintl.o utility/fcintl.c
objectfiles/genlist.o: utility/genlist.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/genlist.o utility/genlist.c
objectfiles/hash.o: utility/hash.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/hash.o utility/hash.c
objectfiles/inputfile.o: utility/inputfile.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/inputfile.o utility/inputfile.c
objectfiles/ioz.o: utility/ioz.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ioz.o utility/ioz.c
objectfiles/iterator.o: utility/iterator.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/iterator.o utility/iterator.c
objectfiles/log.o: utility/log.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/log.o utility/log.c
objectfiles/md5.o: utility/md5.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/md5.o utility/md5.c
objectfiles/mem.o: utility/mem.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/mem.o utility/mem.c
objectfiles/netintf.o: utility/netintf.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/netintf.o utility/netintf.c
objectfiles/pqueue.o: utility/pqueue.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/pqueue.o utility/pqueue.c
objectfiles/rand.o: utility/rand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/rand.o utility/rand.c
objectfiles/registry.o: utility/registry.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/registry.o utility/registry.c
objectfiles/sbuffer.o: utility/sbuffer.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/sbuffer.o utility/sbuffer.c
objectfiles/shared.o: utility/shared.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/shared.o utility/shared.c
objectfiles/string_vector.o: utility/string_vector.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/string_vector.o utility/string_vector.c
objectfiles/support.o: utility/support.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/support.o utility/support.c
objectfiles/timing.o: utility/timing.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/timing.o utility/timing.c
objectfiles/lapi.o: lua/lapi.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lapi.o lua/lapi.c
objectfiles/lauxlib.o: lua/lauxlib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lauxlib.o lua/lauxlib.c
objectfiles/lbaselib.o: lua/lbaselib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lbaselib.o lua/lbaselib.c
objectfiles/lcode.o: lua/lcode.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lcode.o lua/lcode.c
objectfiles/ldblib.o: lua/ldblib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ldblib.o lua/ldblib.c
objectfiles/ldebug.o: lua/ldebug.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ldebug.o lua/ldebug.c
objectfiles/ldo.o: lua/ldo.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ldo.o lua/ldo.c
objectfiles/ldump.o: lua/ldump.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ldump.o lua/ldump.c
objectfiles/lfunc.o: lua/lfunc.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lfunc.o lua/lfunc.c
objectfiles/lgc.o: lua/lgc.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lgc.o lua/lgc.c
objectfiles/linit.o: lua/linit.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/linit.o lua/linit.c
objectfiles/liolib.o: lua/liolib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/liolib.o lua/liolib.c
objectfiles/llex.o: lua/llex.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/llex.o lua/llex.c
objectfiles/lmathlib.o: lua/lmathlib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lmathlib.o lua/lmathlib.c
objectfiles/lmem.o: lua/lmem.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lmem.o lua/lmem.c
objectfiles/loadlib.o: lua/loadlib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/loadlib.o lua/loadlib.c
objectfiles/lobject.o: lua/lobject.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lobject.o lua/lobject.c
objectfiles/lopcodes.o: lua/lopcodes.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lopcodes.o lua/lopcodes.c
objectfiles/loslib.o: lua/loslib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/loslib.o lua/loslib.c
objectfiles/lparser.o: lua/lparser.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lparser.o lua/lparser.c
objectfiles/lstate.o: lua/lstate.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lstate.o lua/lstate.c
objectfiles/lstring.o: lua/lstring.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lstring.o lua/lstring.c
objectfiles/lstrlib.o: lua/lstrlib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lstrlib.o lua/lstrlib.c
objectfiles/ltable.o: lua/ltable.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ltable.o lua/ltable.c
objectfiles/ltablib.o: lua/ltablib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ltablib.o lua/ltablib.c
objectfiles/ltm.o: lua/ltm.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/ltm.o lua/ltm.c
objectfiles/lundump.o: lua/lundump.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lundump.o lua/lundump.c
objectfiles/lvm.o: lua/lvm.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lvm.o lua/lvm.c
objectfiles/lzio.o: lua/lzio.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/lzio.o lua/lzio.c
objectfiles/print.o: lua/print.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/print.o lua/print.c
objectfiles/tolua_event.o: tolua/tolua_event.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/tolua_event.o tolua/tolua_event.c
objectfiles/tolua_is.o: tolua/tolua_is.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/tolua_is.o tolua/tolua_is.c
objectfiles/tolua_map.o: tolua/tolua_map.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/tolua_map.o tolua/tolua_map.c
objectfiles/tolua_push.o: tolua/tolua_push.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/tolua_push.o tolua/tolua_push.c
objectfiles/tolua_to.o: tolua/tolua_to.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -I. -DHAVE_CONFIG_H  -c -o objectfiles/tolua_to.o tolua/tolua_to.c
