all: freeciv-server
objectfiles.a:  objectfiles/ai.o objectfiles/base.o objectfiles/borders.o objectfiles/capstr.o objectfiles/city.o objectfiles/combat.o objectfiles/connection.o objectfiles/dataio.o objectfiles/diptreaty.o objectfiles/effects.o objectfiles/events.o objectfiles/fc_interface.o objectfiles/featured_text.o objectfiles/game.o objectfiles/government.o objectfiles/idex.o objectfiles/improvement.o objectfiles/map.o objectfiles/movement.o objectfiles/nation.o objectfiles/packets.o objectfiles/packets_gen.o objectfiles/player.o objectfiles/requirements.o objectfiles/research.o objectfiles/spaceship.o objectfiles/specialist.o objectfiles/team.o objectfiles/tech.o objectfiles/terrain.o objectfiles/tile.o objectfiles/unit.o objectfiles/unitlist.o objectfiles/unittype.o objectfiles/version.o objectfiles/vision.o objectfiles/worklist.o objectfiles/aisupport.o objectfiles/caravan.o objectfiles/citymap.o objectfiles/cm.o objectfiles/path_finding.o objectfiles/pf_tools.o objectfiles/aiiface.o objectfiles/auth.o objectfiles/barbarian.o objectfiles/cityhand.o objectfiles/citytools.o objectfiles/cityturn.o objectfiles/civserver.o objectfiles/commands.o objectfiles/connecthand.o objectfiles/console.o objectfiles/diplhand.o objectfiles/diplomats.o objectfiles/edithand.o objectfiles/gamehand.o objectfiles/ggzserver.o objectfiles/handchat.o objectfiles/hand_gen.o objectfiles/maphand.o objectfiles/meta.o objectfiles/notify.o objectfiles/plrhand.o objectfiles/report.o objectfiles/ruleset.o objectfiles/sanitycheck.o objectfiles/savegame2.o objectfiles/savegame.o objectfiles/score.o objectfiles/sernet.o objectfiles/settings.o objectfiles/spacerace.o objectfiles/srv_log.o objectfiles/srv_main.o objectfiles/stdinhand.o objectfiles/techtools.o objectfiles/unithand.o objectfiles/unittools.o objectfiles/voting.o objectfiles/height_map.o objectfiles/mapgen.o objectfiles/mapgen_topology.o objectfiles/startpos.o objectfiles/temperature_map.o objectfiles/utilities.o objectfiles/api_actions.o objectfiles/api_effects.o objectfiles/api_find.o objectfiles/api_gen.o objectfiles/api_intl.o objectfiles/api_methods.o objectfiles/api_notify.o objectfiles/api_specenum.o objectfiles/api_utilities.o objectfiles/script.o objectfiles/script_signal.o objectfiles/advbuilding.o objectfiles/advdata.o objectfiles/advgoto.o objectfiles/advtools.o objectfiles/autoexplorer.o objectfiles/autosettlers.o objectfiles/infracache.o objectfiles/advdiplomacy.o objectfiles/advdomestic.o objectfiles/advmilitary.o objectfiles/advspace.o objectfiles/aiair.o objectfiles/aicity.o objectfiles/aidiplomat.o objectfiles/aiferry.o objectfiles/aiguard.o objectfiles/aihand.o objectfiles/aihunt.o objectfiles/aiparatrooper.o objectfiles/aisettler.o objectfiles/aitech.o objectfiles/aitools.o objectfiles/aiunit.o objectfiles/defaultai.o objectfiles/astring.o objectfiles/bitvector.o objectfiles/capability.o objectfiles/distribute.o objectfiles/fciconv.o objectfiles/fcintl.o objectfiles/fc_utf8.o objectfiles/genhash.o objectfiles/genlist.o objectfiles/inputfile.o objectfiles/ioz.o objectfiles/iterator.o objectfiles/log.o objectfiles/md5.o objectfiles/mem.o objectfiles/netintf.o objectfiles/pqueue.o objectfiles/rand.o objectfiles/registry.o objectfiles/shared.o objectfiles/string_vector.o objectfiles/support.o objectfiles/timing.o objectfiles/lapi.o objectfiles/lauxlib.o objectfiles/lbaselib.o objectfiles/lcode.o objectfiles/ldblib.o objectfiles/ldebug.o objectfiles/ldo.o objectfiles/ldump.o objectfiles/lfunc.o objectfiles/lgc.o objectfiles/linit.o objectfiles/liolib.o objectfiles/llex.o objectfiles/lmathlib.o objectfiles/lmem.o objectfiles/loadlib.o objectfiles/lobject.o objectfiles/lopcodes.o objectfiles/loslib.o objectfiles/lparser.o objectfiles/lstate.o objectfiles/lstring.o objectfiles/lstrlib.o objectfiles/ltable.o objectfiles/ltablib.o objectfiles/ltm.o objectfiles/lundump.o objectfiles/lvm.o objectfiles/lzio.o objectfiles/print.o objectfiles/tolua_event.o objectfiles/tolua_is.o objectfiles/tolua_map.o objectfiles/tolua_push.o objectfiles/tolua_to.o objectfiles/fcparallel.o objectfiles/thpool.o
	ar r objectfiles.a objectfiles/*.o
freeciv-server: objectfiles.a
	gcc -pthread -o freeciv-server objectfiles/*.o -g -lm -lz $(FLAGS)

objectfiles/ai.o: common/ai.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ai.o common/ai.c $(FLAGS)
objectfiles/base.o: common/base.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/base.o common/base.c $(FLAGS)
objectfiles/borders.o: common/borders.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/borders.o common/borders.c $(FLAGS)
objectfiles/capstr.o: common/capstr.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/capstr.o common/capstr.c $(FLAGS)
objectfiles/city.o: common/city.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/city.o common/city.c $(FLAGS)
objectfiles/combat.o: common/combat.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/combat.o common/combat.c $(FLAGS)
objectfiles/connection.o: common/connection.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/connection.o common/connection.c $(FLAGS)
objectfiles/dataio.o: common/dataio.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/dataio.o common/dataio.c $(FLAGS)
objectfiles/diptreaty.o: common/diptreaty.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/diptreaty.o common/diptreaty.c $(FLAGS)
objectfiles/effects.o: common/effects.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/effects.o common/effects.c $(FLAGS)
objectfiles/events.o: common/events.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/events.o common/events.c $(FLAGS)
objectfiles/fc_interface.o: common/fc_interface.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/fc_interface.o common/fc_interface.c $(FLAGS)
objectfiles/featured_text.o: common/featured_text.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/featured_text.o common/featured_text.c $(FLAGS)
objectfiles/game.o: common/game.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/game.o common/game.c $(FLAGS)
objectfiles/government.o: common/government.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/government.o common/government.c $(FLAGS)
objectfiles/idex.o: common/idex.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/idex.o common/idex.c $(FLAGS)
objectfiles/improvement.o: common/improvement.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/improvement.o common/improvement.c $(FLAGS)
objectfiles/map.o: common/map.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/map.o common/map.c $(FLAGS)
objectfiles/movement.o: common/movement.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/movement.o common/movement.c $(FLAGS)
objectfiles/nation.o: common/nation.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/nation.o common/nation.c $(FLAGS)
objectfiles/packets.o: common/packets.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/packets.o common/packets.c $(FLAGS)
objectfiles/packets_gen.o: common/packets_gen.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/packets_gen.o common/packets_gen.c $(FLAGS)
objectfiles/player.o: common/player.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/player.o common/player.c $(FLAGS)
objectfiles/requirements.o: common/requirements.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/requirements.o common/requirements.c $(FLAGS)
objectfiles/research.o: common/research.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/research.o common/research.c $(FLAGS)
objectfiles/spaceship.o: common/spaceship.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/spaceship.o common/spaceship.c $(FLAGS)
objectfiles/specialist.o: common/specialist.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/specialist.o common/specialist.c $(FLAGS)
objectfiles/team.o: common/team.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/team.o common/team.c $(FLAGS)
objectfiles/tech.o: common/tech.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/tech.o common/tech.c $(FLAGS)
objectfiles/terrain.o: common/terrain.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/terrain.o common/terrain.c $(FLAGS)
objectfiles/tile.o: common/tile.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/tile.o common/tile.c $(FLAGS)
objectfiles/unit.o: common/unit.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/unit.o common/unit.c $(FLAGS)
objectfiles/unitlist.o: common/unitlist.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/unitlist.o common/unitlist.c $(FLAGS)
objectfiles/unittype.o: common/unittype.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/unittype.o common/unittype.c $(FLAGS)
objectfiles/version.o: common/version.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/version.o common/version.c $(FLAGS)
objectfiles/vision.o: common/vision.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/vision.o common/vision.c $(FLAGS)
objectfiles/worklist.o: common/worklist.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/worklist.o common/worklist.c $(FLAGS)
objectfiles/aisupport.o: common/aicore/aisupport.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aisupport.o common/aicore/aisupport.c $(FLAGS)
objectfiles/caravan.o: common/aicore/caravan.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/caravan.o common/aicore/caravan.c $(FLAGS)
objectfiles/citymap.o: common/aicore/citymap.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/citymap.o common/aicore/citymap.c $(FLAGS)
objectfiles/cm.o: common/aicore/cm.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/cm.o common/aicore/cm.c $(FLAGS)
objectfiles/path_finding.o: common/aicore/path_finding.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/path_finding.o common/aicore/path_finding.c $(FLAGS)
objectfiles/pf_tools.o: common/aicore/pf_tools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/pf_tools.o common/aicore/pf_tools.c $(FLAGS)
objectfiles/aiiface.o: server/aiiface.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aiiface.o server/aiiface.c $(FLAGS)
objectfiles/auth.o: server/auth.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/auth.o server/auth.c $(FLAGS)
objectfiles/barbarian.o: server/barbarian.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/barbarian.o server/barbarian.c $(FLAGS)
objectfiles/cityhand.o: server/cityhand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/cityhand.o server/cityhand.c $(FLAGS)
objectfiles/citytools.o: server/citytools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/citytools.o server/citytools.c $(FLAGS)
objectfiles/cityturn.o: server/cityturn.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/cityturn.o server/cityturn.c $(FLAGS)
objectfiles/civserver.o: server/civserver.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/civserver.o server/civserver.c $(FLAGS)
objectfiles/commands.o: server/commands.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/commands.o server/commands.c $(FLAGS)
objectfiles/connecthand.o: server/connecthand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/connecthand.o server/connecthand.c $(FLAGS)
objectfiles/console.o: server/console.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/console.o server/console.c $(FLAGS)
objectfiles/diplhand.o: server/diplhand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/diplhand.o server/diplhand.c $(FLAGS)
objectfiles/diplomats.o: server/diplomats.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/diplomats.o server/diplomats.c $(FLAGS)
objectfiles/edithand.o: server/edithand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/edithand.o server/edithand.c $(FLAGS)
objectfiles/gamehand.o: server/gamehand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/gamehand.o server/gamehand.c $(FLAGS)
objectfiles/ggzserver.o: server/ggzserver.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ggzserver.o server/ggzserver.c $(FLAGS)
objectfiles/handchat.o: server/handchat.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/handchat.o server/handchat.c $(FLAGS)
objectfiles/hand_gen.o: server/hand_gen.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/hand_gen.o server/hand_gen.c $(FLAGS)
objectfiles/maphand.o: server/maphand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/maphand.o server/maphand.c $(FLAGS)
objectfiles/meta.o: server/meta.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/meta.o server/meta.c $(FLAGS)
objectfiles/notify.o: server/notify.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/notify.o server/notify.c $(FLAGS)
objectfiles/plrhand.o: server/plrhand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/plrhand.o server/plrhand.c $(FLAGS)
objectfiles/report.o: server/report.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/report.o server/report.c $(FLAGS)
objectfiles/ruleset.o: server/ruleset.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ruleset.o server/ruleset.c $(FLAGS)
objectfiles/sanitycheck.o: server/sanitycheck.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/sanitycheck.o server/sanitycheck.c $(FLAGS)
objectfiles/savegame2.o: server/savegame2.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/savegame2.o server/savegame2.c $(FLAGS)
objectfiles/savegame.o: server/savegame.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/savegame.o server/savegame.c $(FLAGS)
objectfiles/score.o: server/score.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/score.o server/score.c $(FLAGS)
objectfiles/sernet.o: server/sernet.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/sernet.o server/sernet.c $(FLAGS)
objectfiles/settings.o: server/settings.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/settings.o server/settings.c $(FLAGS)
objectfiles/spacerace.o: server/spacerace.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/spacerace.o server/spacerace.c $(FLAGS)
objectfiles/srv_log.o: server/srv_log.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/srv_log.o server/srv_log.c $(FLAGS)
objectfiles/srv_main.o: server/srv_main.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/srv_main.o server/srv_main.c $(FLAGS)
objectfiles/stdinhand.o: server/stdinhand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/stdinhand.o server/stdinhand.c $(FLAGS)
objectfiles/techtools.o: server/techtools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/techtools.o server/techtools.c $(FLAGS)
objectfiles/unithand.o: server/unithand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/unithand.o server/unithand.c $(FLAGS)
objectfiles/unittools.o: server/unittools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/unittools.o server/unittools.c $(FLAGS)
objectfiles/voting.o: server/voting.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/voting.o server/voting.c $(FLAGS)
objectfiles/height_map.o: server/generator/height_map.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/height_map.o server/generator/height_map.c $(FLAGS)
objectfiles/mapgen.o: server/generator/mapgen.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/mapgen.o server/generator/mapgen.c $(FLAGS)
objectfiles/mapgen_topology.o: server/generator/mapgen_topology.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/mapgen_topology.o server/generator/mapgen_topology.c $(FLAGS)
objectfiles/startpos.o: server/generator/startpos.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/startpos.o server/generator/startpos.c $(FLAGS)
objectfiles/temperature_map.o: server/generator/temperature_map.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/temperature_map.o server/generator/temperature_map.c $(FLAGS)
objectfiles/utilities.o: server/generator/utilities.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/utilities.o server/generator/utilities.c $(FLAGS)
objectfiles/api_actions.o: server/scripting/api_actions.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/api_actions.o server/scripting/api_actions.c $(FLAGS)
objectfiles/api_effects.o: server/scripting/api_effects.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/api_effects.o server/scripting/api_effects.c $(FLAGS)
objectfiles/api_find.o: server/scripting/api_find.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/api_find.o server/scripting/api_find.c $(FLAGS)
objectfiles/api_gen.o: server/scripting/api_gen.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/api_gen.o server/scripting/api_gen.c $(FLAGS)
objectfiles/api_intl.o: server/scripting/api_intl.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/api_intl.o server/scripting/api_intl.c $(FLAGS)
objectfiles/api_methods.o: server/scripting/api_methods.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/api_methods.o server/scripting/api_methods.c $(FLAGS)
objectfiles/api_notify.o: server/scripting/api_notify.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/api_notify.o server/scripting/api_notify.c $(FLAGS)
objectfiles/api_specenum.o: server/scripting/api_specenum.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/api_specenum.o server/scripting/api_specenum.c $(FLAGS)
objectfiles/api_utilities.o: server/scripting/api_utilities.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/api_utilities.o server/scripting/api_utilities.c $(FLAGS)
objectfiles/script.o: server/scripting/script.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/script.o server/scripting/script.c $(FLAGS)
objectfiles/script_signal.o: server/scripting/script_signal.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/script_signal.o server/scripting/script_signal.c $(FLAGS)
objectfiles/advbuilding.o: server/advisors/advbuilding.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/advbuilding.o server/advisors/advbuilding.c $(FLAGS)
objectfiles/advdata.o: server/advisors/advdata.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/advdata.o server/advisors/advdata.c $(FLAGS)
objectfiles/advgoto.o: server/advisors/advgoto.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/advgoto.o server/advisors/advgoto.c $(FLAGS)
objectfiles/advtools.o: server/advisors/advtools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/advtools.o server/advisors/advtools.c $(FLAGS)
objectfiles/autoexplorer.o: server/advisors/autoexplorer.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/autoexplorer.o server/advisors/autoexplorer.c $(FLAGS)
objectfiles/autosettlers.o: server/advisors/autosettlers.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/autosettlers.o server/advisors/autosettlers.c $(FLAGS)
objectfiles/infracache.o: server/advisors/infracache.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/infracache.o server/advisors/infracache.c $(FLAGS)
objectfiles/advdiplomacy.o: ai/advdiplomacy.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/advdiplomacy.o ai/advdiplomacy.c $(FLAGS)
objectfiles/advdomestic.o: ai/advdomestic.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/advdomestic.o ai/advdomestic.c $(FLAGS)
objectfiles/advmilitary.o: ai/advmilitary.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/advmilitary.o ai/advmilitary.c $(FLAGS)
objectfiles/advspace.o: ai/advspace.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/advspace.o ai/advspace.c $(FLAGS)
objectfiles/aiair.o: ai/aiair.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aiair.o ai/aiair.c $(FLAGS)
objectfiles/aicity.o: ai/aicity.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aicity.o ai/aicity.c $(FLAGS)
objectfiles/aidiplomat.o: ai/aidiplomat.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aidiplomat.o ai/aidiplomat.c $(FLAGS)
objectfiles/aiferry.o: ai/aiferry.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aiferry.o ai/aiferry.c $(FLAGS)
objectfiles/aiguard.o: ai/aiguard.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aiguard.o ai/aiguard.c $(FLAGS)
objectfiles/aihand.o: ai/aihand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aihand.o ai/aihand.c $(FLAGS)
objectfiles/aihunt.o: ai/aihunt.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aihunt.o ai/aihunt.c $(FLAGS)
objectfiles/aiparatrooper.o: ai/aiparatrooper.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aiparatrooper.o ai/aiparatrooper.c $(FLAGS)
objectfiles/aisettler.o: ai/aisettler.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aisettler.o ai/aisettler.c $(FLAGS)
objectfiles/aitech.o: ai/aitech.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aitech.o ai/aitech.c $(FLAGS)
objectfiles/aitools.o: ai/aitools.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aitools.o ai/aitools.c $(FLAGS)
objectfiles/aiunit.o: ai/aiunit.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/aiunit.o ai/aiunit.c $(FLAGS)
objectfiles/defaultai.o: ai/defaultai.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/defaultai.o ai/defaultai.c $(FLAGS)
objectfiles/astring.o: utility/astring.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/astring.o utility/astring.c $(FLAGS)
objectfiles/bitvector.o: utility/bitvector.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/bitvector.o utility/bitvector.c $(FLAGS)
objectfiles/capability.o: utility/capability.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/capability.o utility/capability.c $(FLAGS)
objectfiles/distribute.o: utility/distribute.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/distribute.o utility/distribute.c $(FLAGS)
objectfiles/fciconv.o: utility/fciconv.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/fciconv.o utility/fciconv.c $(FLAGS)
objectfiles/fcintl.o: utility/fcintl.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/fcintl.o utility/fcintl.c $(FLAGS)
objectfiles/fc_utf8.o: utility/fc_utf8.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/fc_utf8.o utility/fc_utf8.c $(FLAGS)
objectfiles/genhash.o: utility/genhash.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/genhash.o utility/genhash.c $(FLAGS)
objectfiles/genlist.o: utility/genlist.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/genlist.o utility/genlist.c $(FLAGS)
objectfiles/inputfile.o: utility/inputfile.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/inputfile.o utility/inputfile.c $(FLAGS)
objectfiles/ioz.o: utility/ioz.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ioz.o utility/ioz.c $(FLAGS)
objectfiles/iterator.o: utility/iterator.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/iterator.o utility/iterator.c $(FLAGS)
objectfiles/log.o: utility/log.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/log.o utility/log.c $(FLAGS)
objectfiles/md5.o: utility/md5.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/md5.o utility/md5.c $(FLAGS)
objectfiles/mem.o: utility/mem.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/mem.o utility/mem.c $(FLAGS)
objectfiles/netintf.o: utility/netintf.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/netintf.o utility/netintf.c $(FLAGS)
objectfiles/pqueue.o: utility/pqueue.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/pqueue.o utility/pqueue.c $(FLAGS)
objectfiles/rand.o: utility/rand.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/rand.o utility/rand.c $(FLAGS)
objectfiles/registry.o: utility/registry.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/registry.o utility/registry.c $(FLAGS)
objectfiles/shared.o: utility/shared.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/shared.o utility/shared.c $(FLAGS)
objectfiles/string_vector.o: utility/string_vector.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/string_vector.o utility/string_vector.c $(FLAGS)
objectfiles/support.o: utility/support.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/support.o utility/support.c $(FLAGS)
objectfiles/timing.o: utility/timing.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/timing.o utility/timing.c $(FLAGS)
objectfiles/lapi.o: lua/lapi.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lapi.o lua/lapi.c $(FLAGS)
objectfiles/lauxlib.o: lua/lauxlib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lauxlib.o lua/lauxlib.c $(FLAGS)
objectfiles/lbaselib.o: lua/lbaselib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lbaselib.o lua/lbaselib.c $(FLAGS)
objectfiles/lcode.o: lua/lcode.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lcode.o lua/lcode.c $(FLAGS)
objectfiles/ldblib.o: lua/ldblib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ldblib.o lua/ldblib.c $(FLAGS)
objectfiles/ldebug.o: lua/ldebug.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ldebug.o lua/ldebug.c $(FLAGS)
objectfiles/ldo.o: lua/ldo.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ldo.o lua/ldo.c $(FLAGS)
objectfiles/ldump.o: lua/ldump.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ldump.o lua/ldump.c $(FLAGS)
objectfiles/lfunc.o: lua/lfunc.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lfunc.o lua/lfunc.c $(FLAGS)
objectfiles/lgc.o: lua/lgc.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lgc.o lua/lgc.c $(FLAGS)
objectfiles/linit.o: lua/linit.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/linit.o lua/linit.c $(FLAGS)
objectfiles/liolib.o: lua/liolib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/liolib.o lua/liolib.c $(FLAGS)
objectfiles/llex.o: lua/llex.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/llex.o lua/llex.c $(FLAGS)
objectfiles/lmathlib.o: lua/lmathlib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lmathlib.o lua/lmathlib.c $(FLAGS)
objectfiles/lmem.o: lua/lmem.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lmem.o lua/lmem.c $(FLAGS)
objectfiles/loadlib.o: lua/loadlib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/loadlib.o lua/loadlib.c $(FLAGS)
objectfiles/lobject.o: lua/lobject.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lobject.o lua/lobject.c $(FLAGS)
objectfiles/lopcodes.o: lua/lopcodes.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lopcodes.o lua/lopcodes.c $(FLAGS)
objectfiles/loslib.o: lua/loslib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/loslib.o lua/loslib.c $(FLAGS)
objectfiles/lparser.o: lua/lparser.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lparser.o lua/lparser.c $(FLAGS)
objectfiles/lstate.o: lua/lstate.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lstate.o lua/lstate.c $(FLAGS)
objectfiles/lstring.o: lua/lstring.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lstring.o lua/lstring.c $(FLAGS)
objectfiles/lstrlib.o: lua/lstrlib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lstrlib.o lua/lstrlib.c $(FLAGS)
objectfiles/ltable.o: lua/ltable.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ltable.o lua/ltable.c $(FLAGS)
objectfiles/ltablib.o: lua/ltablib.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ltablib.o lua/ltablib.c $(FLAGS)
objectfiles/ltm.o: lua/ltm.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/ltm.o lua/ltm.c $(FLAGS)
objectfiles/lundump.o: lua/lundump.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lundump.o lua/lundump.c $(FLAGS)
objectfiles/lvm.o: lua/lvm.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lvm.o lua/lvm.c $(FLAGS)
objectfiles/lzio.o: lua/lzio.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/lzio.o lua/lzio.c $(FLAGS)
objectfiles/print.o: lua/print.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/print.o lua/print.c $(FLAGS)
objectfiles/tolua_event.o: tolua/tolua_event.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/tolua_event.o tolua/tolua_event.c $(FLAGS)
objectfiles/tolua_is.o: tolua/tolua_is.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/tolua_is.o tolua/tolua_is.c $(FLAGS)
objectfiles/tolua_map.o: tolua/tolua_map.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/tolua_map.o tolua/tolua_map.c $(FLAGS)
objectfiles/tolua_push.o: tolua/tolua_push.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/tolua_push.o tolua/tolua_push.c $(FLAGS)
objectfiles/tolua_to.o: tolua/tolua_to.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/tolua_to.o tolua/tolua_to.c $(FLAGS)
objectfiles/fcparallel.o: parallel/fcparallel.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/fcparallel.o parallel/fcparallel.c $(FLAGS)
objectfiles/thpool.o: parallel/thpool.c
	gcc -Iserver -Iserver/generator -Iserver/scripting -Iserver/advisors -Icommon -Icommon/aicore -Iutility -Iai -Ilua -Itolua -Iparallel -I. -DHAVE_CONFIG_H  -g -c -o objectfiles/thpool.o parallel/thpool.c $(FLAGS)
