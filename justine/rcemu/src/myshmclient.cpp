/**
 * @brief Justine - this is a rapid prototype for development of Robocar City Emulator
 *
 * @file myshmclient.cpp
 * @author  Norbert Bátfai <nbatfai@gmail.com>
 * @version 0.0.10
 *
 * @section LICENSE
 *
 * Copyright (C) 2014 Norbert Bátfai, batfai.norbert@inf.unideb.hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 * Robocar City Emulator and Robocar World Championship
 *
 * desc
 *
 */

#include <myshmclient.hpp>
//#include <trafficlexer.hpp>
#define DIST 2000
//#define DEBUG
//#define ASKMAXG
#define IterationS
char data[524288];

void
justine::sampleclient::MyShmClient::car (boost::asio::ip::tcp::socket & socket, int id, unsigned *f,unsigned *t, unsigned *s)
{

  boost::system::error_code err;

  size_t
    length = std::sprintf (data, "<car ");
  length += std::sprintf (data + length, "%d>", id);

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);
    }

  int
    idd
  {
  0};
  std::sscanf (data, "<OK %d %u %u %u", &idd, f, t, s);

  //std::cout.write ( data, length );
  //std::cout << "Command CAR sent." << std::endl;

}

//mégis csak írunk egy függvény ami szépen visszaadja majd nekünk azt hogy a gengszterek egymáshoz képest milyen messze helyeszkednek el itt is szépen berendezzük melyik gengszterhez hányan vannak a legközelebb
//igazából ez csak prototípusként lényeges, lehetséges hogy nem is haszáljuk majd csak a működése végett vagyunk kíváncsiak hogy esetleges teljesítménynövekedést érünk-e el vele



justine::sampleclient::MyShmClient::Gangster justine::sampleclient::MyShmClient::gengitavok (boost::asio::ip::tcp::socket & socket)
{

  boost::system::error_code err;

  /*size_t length = std::sprintf (data, "<gangsters ");
  length += std::sprintf (data + length, ">");

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);
    }
*/
  //lényeg :D


  /* reading all gangsters into a vector */
  int idd{0};
  unsigned f,t,s;
  unsigned int g;
  int n{0};
  int nn{0};
  //gengi vektor
  std::vector < Gangster > gangsters;
  //ugyanúgy beaddoljuk a gengiket egy vektorba
  while (std:: sscanf (data + nn, "<OK %d %u %u %u>%n", &idd, &f, &t, &s, &n) == 4) //
    {
      nn += n;
      gangsters.push_back (Gangster{idd, f, t, (int)s});
    }

  //rendezzük őket nem egy rendőrhöz képest hanem egymáshoz :O
  //tehát mindig kiválasztunk egy gengit és

  Gangster gl,rg;
  int max = 0;
  for(auto it = gangsters.begin(); it != gangsters.end(); it++)
  {
	gl = *it;
	gl.neargang = 0;

  	for(int i = 0; i < (int)gangsters.size(); i++)
  	{
  		g = gangsters[i].to;
  		if( dst(gl.to,g) < 2000)
  		{
  			gl.neargang++;
  		}
  	}
  	if(gl.neargang > max)
  	{
  		max = gl.neargang;
  		rg = gl;
  	}

  }
 /* std::sort (gangsters.begin (), gangsters.end (),[] (Gangster x, Gangster y)
  {
     return x.neargang > y.neargang;

  }
  );*/

  //g = gangsters[0];


  //auto *it = gangsters.begin();


  //std::cout << "Legtöbb gengis:"<< gl.id << " G sz:" << gl.neargang << std::endl;
  //std::cout.write ( data, length );
  //std::cout << "Command GANGSTER sent." << std::endl;
  //std::cout.write ( data, length );
 // std::cout << "Command GENGI sent." << std::endl;
  return rg;

}



std::vector < justine::sampleclient::MyShmClient::Gangster >justine::sampleclient::MyShmClient::gangsters (boost::asio::ip::tcp::socket & socket, int id, osmium:: unsigned_object_id_type cop, Gangster * rg){

  boost::system::error_code err;

  size_t
    length = std::sprintf (data, "<gangsters ");
  length += std::sprintf (data + length, "%d>", id);

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);
    }

  /* reading all gangsters into a vector */
  int idd{0};
  unsigned f,t;
  int s;
  int n{0};
  int nn{0};
  std::vector < Gangster > gangsters;

  while (std::sscanf (data + nn, "<OK %d %u %u %u>%n", &idd, &f, &t, &s, &n) == 4) //
    {
      nn += n;
      gangsters.push_back (Gangster{idd, f, t, s});
    }

 std::sort (gangsters.begin (), gangsters.end (),
	     [this, cop] (Gangster x, Gangster y)
	     {
	     return dst (cop, x.to) < dst (cop, y.to);}
  );
#ifdef ASKMAXG
  Gangster gl;
  int max = 0;
  for(auto it = gangsters.begin(); it != gangsters.end(); it++)
  {
	gl = *it;
	gl.neargang = 0;

  	for(int i = 0; i < (int)gangsters.size(); i++)
  	{
  		//g = ;
  		if( dst(gl.to,gangsters[i].to) < 2000)
  		{
  			gl.neargang++;
  		}
  	}
  	if(gl.neargang > max)
  	{
  		max = gl.neargang;
  		*rg = gl;
  	}

  }
#endif
  //std::cout.write ( data, length );
  //std::cout << "Command GANGSTER sent." << std::endl;

  return gangsters;
}

std::vector < justine::sampleclient::MyShmClient::Cop >
  justine::sampleclient::MyShmClient::initcops (boost::asio::ip::tcp::
						socket & socket)
{

  boost::system::error_code err;

  size_t
    length =
    std::sprintf (data, "<init guided %s 10 c>", m_teamname.c_str ());

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);


  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);
    }

  /* reading all gangsters into a vector */
  int idd{0};
  int f,t;
  char c;
  int n{0};
  int nn{0};
  std::vector < Cop > cops;

  while (std::
	 sscanf (data + nn, "<OK %d %d/%d %c>%n", &idd, &f, &t, &c, &n) == 4)
    {
      nn += n;
      cops.push_back (idd);
    }

 // std::cout.write (data, length);
  //std::cout << "Command INIT sent." << std::endl;

  return cops;
}


int
justine::sampleclient::MyShmClient::init (boost::asio::ip::tcp::socket & socket)
{

  boost::system::error_code err;

  size_t
    length = std::sprintf (data, "<init guided %s 1 c>", m_teamname.c_str ());

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);

    }

  int
    id
  {
  0};
  std::sscanf (data, "<OK %d", &id);

  //std::cout.write (data, length);
  //std::cout << "Command INIT sent." << std::endl;

  return id;

}

void
justine::sampleclient::MyShmClient::pos (boost::asio::ip::tcp::
					 socket & socket, int id)
{

  boost::system::error_code err;

  size_t
    length = std::sprintf (data, "<pos ");
  length +=
    std::sprintf (data + length, "%d %u %u>", id, 2969934868u, 651365957u);

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);

    }

  //std::cout.write (data, length);
  //std::cout << "Command POS sent." << std::endl;
}



void
justine::sampleclient::MyShmClient::route (boost::asio::ip::tcp::socket & socket, int id,std::vector <osmium::unsigned_object_id_type >&path){

  boost::system::error_code err;

  size_t length = std::sprintf (data,"<route %lu %d", path.size (), id);

  for (auto ui:path){

  	length += std::sprintf (data + length, " %lu", ui);
  }

  length += std::sprintf (data + length, ">");

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);

    }

  //std::cout.write (data, length);
  //std::cout << "Command ROUTE sent." << std::endl;

}

void
justine::sampleclient::MyShmClient::start (boost::asio::io_service & io_service,const char *port)
{

#ifdef DEBUG
  foo ();
#endif

  boost::asio::ip::tcp::resolver resolver (io_service);
  boost::asio::ip::tcp::resolver::query query (boost::asio::ip::tcp::v4 (),"localhost", port);
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve (query);

  boost::asio::ip::tcp::socket socket (io_service);
  boost::asio::connect (socket, iterator);

  int id = init (socket);

  pos (socket, id);

  unsigned int
    g{0u}, gg{0u}, f{0u}, t{0u}, s{0u};

  car (socket, id, &f, &t, &s);
  //gangstereket egy vectorba menjtük
  std::vector < Gangster > gngstrs;
  std::vector < Gangster >::iterator it;
  int GC = 0;
  justine::sampleclient::MyShmClient::Gangster MG;
  //végtelen ciklussal "futtatjuk" az algoritmusunkat
  for (;;)
    {

      std::this_thread::sleep_for (std::chrono::milliseconds (200));
	  //MG = gengitavok(socket);
      car (socket, id, &f, &t, &s);

      gngstrs = gangsters (socket, id, t,&MG);

      if (gngstrs.size () > 0){

			g = gngstrs[0].to;
	  }

	  else{

			g = 0;
	  }

      if (g > 0){

		  //std::cout << "\n";
		  //gatlag /= i;
		  //sleep (1);
		  //std::cout << "A:" << gatlag << "\n";
		  GC = 0;
		  for(int i = 0; i < (int)gngstrs.size(); i++){

		    gg = gngstrs[i].to;
		    if(dst(t,gg) < DIST){

		      	GC++;

		    }
		  }

	  std::cout<< DIST <<"egységnyi távolságon belüli gengszterek száma:" << GC <<std::endl;
	  std::vector <osmium::unsigned_object_id_type> pathG = hasDijkstraPath(t,MG.to);
	  std::vector < osmium::unsigned_object_id_type > path = hasDijkstraPath (t, g);
      std::cout << "Legtöbb gengis és a rendőrbácsi távolsága:" << dst(t,MG.to) << " gengijei:"<< MG.neargang <<std::endl;

	  if (path.size () > 1){

		 if(dst(t,MG.to) < DIST*2){

		      //std::copy ( path.begin(), path.end(),
		      //          std::ostream_iterator<osmium::unsigned_object_id_type> ( std::cout, " -> " ) );
				std::cout << "Legközelebbi gengit kergetem!" << std::endl;
		      route (socket, id, path);
		     }

	     else{

	     	std::cout << "legtöbb gengishez megyek! - " << MG.to << " gengijei:"<< MG.neargang <<std::endl;
	     	route(socket,id,pathG);
	     }

	    }
	}
  }
}



//Routolhat-e a rendőrünk egy gengszter irányába?
// std::vector<Cop> cops, Cop mycop
bool justine::sampleclient::MyShmClient::CanIRoute(unsigned int cops_route_id[], int cop_index, unsigned int gangster, int initialized_Cops)
{
    //int p = cop_index;
    bool Route = true;
   for (int i = 0; i < initialized_Cops; i++) {
      if (cops_route_id[i] == gangster) {
	std::cout << "Sorry I can not route to "<< gangster << "because "<< i<<" is routing to it."<<std::endl;
	return false;	  
	
      } 
    }
   /* if (Route == true) {
	std::cout << "Can I route?\nYes,I can route to: "<< gangster<<std::endl;
      }*/
    /*if (Route == true) {
       std::cout << "I can route to "+ gangster << std::endl;
    } else {
      std::cout << "I can NOT route to "+ gangster << std::endl;
    }*/
   return Route;
}



void
justine::sampleclient::MyShmClient::start10 (boost::asio::io_service & io_service,const char *port)
{
  
/*#ifdef DEBUG
  foo ();
#endif*/

  boost::asio::ip::tcp::resolver resolver (io_service);
  boost::asio::ip::tcp::resolver::query query (boost::asio::ip::tcp::v4 (),"localhost", port);
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve (query);

  boost::asio::ip::tcp::socket socket (io_service);
  boost::asio::connect (socket, iterator);

  std::vector < Cop > cops = initcops (socket);

  unsigned int g{0u}, gg{0u}, from{0u}, to{0u}, step{0u};
  //unsigned int actual_cop_from{0u}, actual_cop_step{0u}, actual_cop_to{0u};
  std::vector < Gangster > gngstrs,gtavok;
  int Initialized_Cops = 10;
  int Actual_Cop = 0;
  //int CopOk[10] = {0,0,0,1,1,1,1,1,1,1};
  //int Help [10] = {0};
  //védéshez kellett...
  //unsigned int  MGC = 2000;
  //bool isMade = false;
  //GD a distancehez kell ebben tároljuk el milyen ...
  //unsigned int GD[11] = {0};
  //GP lesz a gengszterek száma rendőrönként
  unsigned int GP[11] = {0};
  //Hova megy a zsarunk - csak natúr nore-ra
  //unsigned int CopToNode[10];
  //Max Gengszter szám
  unsigned int MGP {0u};
  //Ki a boss cop, az Ő "to" útja amerre megy.
  unsigned int BCOP = 0;
  //Boss cop ID-je
  unsigned int BCOPID = 0;
  //A boss cop felé routelünk -e vagy sem
  //Lehet hogy felesleges lesz de, 0 - a legközelebbi gengsztereket kapja el, 1 - boss cop felé routel, 2 - elindult a legtöbb gengszterrel rendelkező gengszter felé
  unsigned int BCOPR[10] = {0};
  //hova routel az x.-edik rendőrünk - gengszter felé
  unsigned int Cop_route_ID[10] = {0};
  //Aktuális rendőr és gengszter távolsága
  unsigned int Cop_Gangster_Distance;
  //Routelhatunk-e vagy sem.
  //bool CopRoute;
  //Lehet hogy felesleges lesz de, 0 - a legközelebbi gengsztereket kapja el, 1 - boss cop felé routel, 2 - elindult a legtöbb gengszterrel rendelkező gengszter felé
  //unsigned int Cop_Status[10] = {0};
  unsigned int Iteration = 1;
  justine::sampleclient::MyShmClient::Gangster MG;
  std::vector<osmium::unsigned_object_id_type> path[10];
  
  /*------------------------------------------------------------------------------------------------------------------------------------------------------*/
  //v.0.1
  //Rádius keresés - mérték egyenlőre állandó vagy dinamikusan az aktuális helyzetekhez kialakított
  //Gengszterek számának meghatározása "területenként", az aktuális egységnyi sugarú "körön" belül
  //Akinél nincs gengszter elindul a legközelebb lévő rendőrhöz hogy segítsen neki.
  //Menet közben ha talál gengsztert és az legalább a fele mint amelyik rendőrhöz indul akkor üldözés üzemmódba vált.
  //Ha egy rendőr kerületében több mint X (egyenlőre ez a szám legyen 6-7-8) akkor segítséget hív és a legközelebbi tétlen rendőrt magához rendeli
  //a nagyobb gengszterfogás érdekében
  //meglehet állapítani hogy két útvonal megyezik-e vagy sem

  /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  
  //TODO:
  //távolságok lekérése - vektorban való tárolás (nekem ez most tömb lesz v.0.1) - pipa 
  //ezzel együtt mindig a legnagyobb gengszterrel rendelkező rendőr eltárolása - NODE ID (mindig t változó lesz) - pipa 
  //tevékenység vektor - alapból mindenki járőrözik - pipa
  //segítség vektor - lényegében egy bitvektor ami ha úgy gondolja az algoritmusunk akkor átállítja 1-re az aktuális rendőrét és ezzel kiküldve a jelet a többi társnak
  //egyenlőre semmiféle újabb függvényt nem írunk csak egyszerűen az alap működést próbáljuk belőni majd a lentebb levő végtelen ciklusban :)
  //két rendőr ne menjen ugyan arra a node-ra, ezt tömb segítségével....
  //mindig lesz egy kitüntetett rendőr aki a legtöbb gengivel rendelkezik.
  //kíváncsi vagyok az eredményre
  //2015 04 16
  /*---------------------------------------------------------------------------------------------------------------------------------------------------*/

  //Debrecen5 - re el kell hogy készüljön! szeretnénk élesben is tesztelni!
  //Illetve a védési programban is...
  for (;;)
    {

      std::this_thread::sleep_for (std::chrono::milliseconds (200));
      
      //A p lesz nekünk mindig az aktuális index, szükségszerűen most itt nullázik ki.
      Actual_Cop = 0;
      //isMade = false;
      MGP = 0;
      //BCOPR[p] = 0;
#ifdef IterationS
      std::cout << "----------------------- "<< Iteration++ <<" -----------------------------"<< std::endl;
#endif
      //lekérjük az MG változóba a legnagyobb gegszterszámmal rendelkező gengsztert...
      //MG = gengitavok(socket);
#ifdef DEBUG
      std::cout << "Max gangster around the boss gangster: " << MG.neargang << std::endl;
#endif
      //for ciklussal fogjuk bejárni a cop vektorunkat, ebben a verzióban én most lecseréltem az auto cop:cops -os bejárást,
      //jelenelg nekem az iterátoros megoldás jobban tetszik :)
      //előbb számolunk körzetet hogy ne gabajodjanak össze a rendőrök.
      for (auto it = cops.begin(); it != cops.end(); it++) {
	       //kinullázik a GP-t minden egyes iterációban.
	      GP[Actual_Cop] = 0;
	      //itt lekérjük kisautót 
	      car (socket, *it, &from, &to, &step);
	      
	      for (int i = 0; i < (int) gngstrs.size(); i++) {

		      gngstrs = gangsters (socket, *it, to,&MG);
		      gg = gngstrs[i].to;
		      if (dst(to,gg) < DIST) {

				GP[Actual_Cop]++;
				//std::cout << "GP["<< Actual_Cop <<"]"<< GP[Actual_Cop] << std::endl;

		      }
		}

		if (GP[Actual_Cop] > MGP) {
		  
			      BCOP = to;
			      BCOPID = Actual_Cop;
			      MGP = GP[Actual_Cop];
		}
		
		Actual_Cop++;
      }
      Cop_Gangster_Distance = dst(to,MG.to);
      Actual_Cop = 0;
      std::cout << "Maximum Gangster around the 'Boss' COP:" << MGP <<  std::endl;
      
      //for ciklussal fogjuk bejárni a cop vektorunkat, ebben a verzióban én most lecseréltem az auto cop:cops -os bejárást, jelenelg nekem az iterátoros megoldás jobban tetszik :)
      for (auto it = cops.begin(); it != cops.end(); it++) {

	    //car függvény meghívása, f- honnan ,t - hova, s - hanyadik lépésnél járhat (tipp)
	    car (socket, *it, &from, &to, &step);
	    Cop_route_ID[Actual_Cop] = to;
	    gngstrs = gangsters (socket, *it, to,&MG);
	    if (Actual_Cop == BCOPID) {
	      //std::cout << "I am the boss cop, ID:"<<Actual_Cop<<std::endl;
	    }
	    //std::cout << "Rendor:" << *it << " Honnan:" << f << " Hova:" << t << " Lépés:" << s << std::endl;
	  
	    //Megnézzük hogy a gengszter vektorunk üres -e vagy sem. (van e éppen gengszter felcsatolva vagy sem?!)
	    //if (gngstrs.size () > 0) {
		//mivel a gangster függvényünk szépen rendezte a vektorunk ezért a 0. elem mindig az aktuális rendőrhöz legközelebb eső gengsztert adja vissza
		//g = gngstrs[0].to;
		//gl = gngstrs[gngstrs.size () - 1].to;
	      //} else {
		//ha nincs gengi akkor legyen 0
		//g = 0;
	      //}

	    //össze szeretném gyűjteni a rendőrök X egységnyi sugarán belüli gengsztereket,
	    //és ezek alapján eldönteni hogy melyik "területen" érdemes a gengsztereket üldözni
	    //ha van gengink akkor szépen lőjük az algoritmust

	    if (gngstrs.size() > 0) {
		//auto itc = cops.begin();
		//itt megnézzük hogy milyen közel vagyunk az aktuális rendőrrel az esetleges kitüntetett rendőrünkhöz
		/*for (int i = 0;  i < Initialized_Cops; i++, itc++) {

			  car (socket, *it, &actual_cop_from, &actual_cop_to, &actual_cop_step);
			  if (i != Actual_Cop) {
			    
					  if (dst(to,actual_cop_to) < DIST/2 && BCOPR[i] == 1) {
						  BCOPR[i] = 0;
					  }
			  }

		}*/
		#ifdef DEBUG
		std::cout << Actual_Cop << ". rendor körzetében " << GP[Actual_Cop] << "gengi..." << std::endl;
		#endif
		//ha nulla a gengszterszám akkor elindulunk a legnagyobb gengivel rendelkező zsaru felé
		//ha 0 vagy a fele kisebb mint a legnagyobb számú rendőré és nem csinál semmit vagy ha a táv kisebb mint X hogyha van a közelében gengi
		//|| ( (GP[Actual_Cop] < MGP/3) && BCOPR[Actual_Cop] == 0)
		if (GP[Actual_Cop] == 0 && BCOPR[Actual_Cop] == 0) {
		  
		      std::vector<osmium::unsigned_object_id_type> nogpath = hasDijkstraPath ( to, BCOP );
		      #ifdef DEBUG
		      std::cout << Actual_Cop << ". rendor elindult a kitüntetett rendőr irányába." << std::endl;
		      #endif
		      BCOPR[Actual_Cop] = 1;
		      Cop_route_ID[Actual_Cop] = BCOPID;
		      route(socket,*it,nogpath);
		      
		//ha már elég közel kerültem a boss cophoz akkor elkezdem begyűjteni a körülette levő gengsztereket, amely hozzám a legközelebb van és persze nem üldözi senki! :)
		} else if ( (BCOPR[Actual_Cop] == 1 && dst(to,BCOP) < DIST) || (BCOPR[Actual_Cop] == 2 && dst(to,MG.to) < DIST ) ) {
		  
			gngstrs = gangsters (socket, *it, to,&MG);
		       for (int i = 0; i < (int)gngstrs.size(); i++) {
			 
				    //g = gngstrs[i].id;
				    if (CanIRoute(Cop_route_ID,Actual_Cop,gngstrs[i].id,Initialized_Cops)) {
					    
					    path[Actual_Cop] = hasDijkstraPath ( to, gngstrs[i].to );
					    Cop_route_ID[Actual_Cop] = gngstrs[i].id;
					    i = gngstrs.size() + 1;					  
				    }					
			}
		      //g = gngstrs[0].to;
		      //path[Actual_Cop] = hasDijkstraPath ( to, g );
		      //Cop_route_ID[Actual_Cop] = gngstrs[0].id;
		      
		      BCOPR[Actual_Cop] = 3;
		      if (path[Actual_Cop].size () > 1) {
			
				route (socket, *it, path[Actual_Cop]);
				
		      }
		//ha egyik sem, úgymond a BCOPR = 0 éppen csak kapkodja a legközelebbi gengsztert akkor elindulok a hozzám legközelebb álló gengszterhez amelyiket nem üldözi senki eddig és begyűjtöm
		} else if (BCOPR[Actual_Cop] == 3) {
			      /*for (int i = 0; i < 10; i++) {
				
				      if (i != Actual_Cop) {
					
					      if (CopToNode[i] != CopToNode[Actual_Cop]) {
						
						      g = gngstrs[0].to;
					      }
				      }
			      }*/
			      gngstrs = gangsters (socket, *it, to,&MG);
			      for (int i = 0; i < (int)gngstrs.size(); i++) {
				
				    //g = gngstrs[i].id;
				    if (CanIRoute(Cop_route_ID,Actual_Cop,gngstrs[i].id,Initialized_Cops)) {
				      
					    path[Actual_Cop] = hasDijkstraPath ( to, gngstrs[i].to );
					    Cop_route_ID[Actual_Cop] = gngstrs[i].id;
					    std::cout << Actual_Cop << " is routing to: "<< Cop_route_ID[Actual_Cop] << " because he can..." << std::endl;
					    i = gngstrs.size()+1;					  
				    }					
			      }
			      
			      //std::vector<osmium::unsigned_object_id_type> pathg = hasDijkstraPath ( g, to );

			      /*if (path[Actual_Cop] == pathg) {
				
				      std::cout << "zsaru és gengszter útvonala megegyezik" << std::endl;
				      
			      }*/
			      
			      if (path[Actual_Cop].size () > 1) {
				
					route (socket, *it, path[Actual_Cop]);
			      }
	      
	      //hogyha a legtöbb gengszterrel rendelkező gengszter van hozzánk közelebb akkor inkább oda menjünk mint a boss cophoz
	      } else if( (Cop_Gangster_Distance < dst(to,BCOP) || (unsigned int) MG.neargang > MGP) && (BCOPR[Actual_Cop] == 0 || BCOPR[Actual_Cop] == 1) ){
		
		path[Actual_Cop] = hasDijkstraPath(to, MG.to);
		Cop_route_ID[Actual_Cop] = MG.id;
		BCOPR[Actual_Cop] = 2;
		 
		if (path[Actual_Cop].size () > 1) {
		  
			  route (socket, *it, path[Actual_Cop]);
		}
		#ifdef DEBUG
		std::cout << Actual_Cop << " is routing to the MAX gangster." << std::endl;
		#endif
	      //Boss Cop mit csinál?! Megy a legközelebbi gengszterre, mindig elsőbsége van.
	      } else {
		  path[Actual_Cop] = hasDijkstraPath ( to, gngstrs[0].to );
		  Cop_route_ID[Actual_Cop] = gngstrs[0].id;
		  if (path[Actual_Cop].size () > 1) {
		    
			    route (socket, *it, path[Actual_Cop]);
		  }
	      }
	  //#ifdef DEBUG
	  std::cout << Actual_Cop <<  ". cop is routing to " << Cop_route_ID[Actual_Cop] << std::endl;
	  //#endif
	  } else {
	    std::cout << "Warning there is no gangster available!" << std::endl;
	  }
	  Actual_Cop++;
	}
    }
}


