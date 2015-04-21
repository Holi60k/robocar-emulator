teamname="HNK"
port=10007
shm="SharedMemory"
nodegps="../debrecen-lmap.txt"
osm="../debrecen.osm"
city="Debrecen"
gangst=100

src/smartcity --osm=$osm --city=$city --shm=$shm --node2gps=$nodegps&
sleep 1
src/traffic --port=$port --shm=$shm&
sleep 1
(sleep 1; echo "<init Norbi $gangst g>"; sleep 1)|telnet localhost $port
sleep 1
src/samplemyshmclient --port=$port --shm=$shm --team=$teamname&
sleep 1
#(sleep 1; echo "<init Norbi $gangst g>"; sleep 1)|telnet localhost $port
##sleep 1
cd ..
cd rcwin
sleep 1
java -jar target/site/justine-rcwin-0.0.16-jar-with-dependencies.jar $nodegps

