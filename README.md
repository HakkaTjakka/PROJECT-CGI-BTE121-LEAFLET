# PROJECT CGI BTE121 LEAFLET
 CGI-BIN CONSTRUCTION FOR LEAFLET SHOWING MINECRAFT BTE121 PROJECTION TILES

Used in combination with:

   https://github.com/HakkaTjakka/Leaflet-Minecraft-Region-Tiles-Map and
   
   https://github.com/HakkaTjakka/REGION_FINDER
  
Makes use of xampp/cgi-bin/texture.cgi (https://github.com/HakkaTjakka/PROJECT-CGI-BTE121-LEAFLET/blob/main/xampp/cgi-bin/texture.cgi)

which points to: F:\PROJECT_CGI_BTE121\bin\project.exe
in my case. Contents of texture.cgi is therefore: #!"F:\PROJECT_CGI_BTE121\bin\project.exe"

The project.exe is used with the Javascript/HTML from https://github.com/HakkaTjakka/Leaflet-Minecraft-Region-Tiles-Map

You need to setup a server like xampp. 

With https://github.com/HakkaTjakka/REGION_FINDER you make the tiles. See discription in repo. The directories used in the index.html from the
Leaflet script, AND those in the texture.cgi from xampp, AND those used in this repo in main.cpp MUST ALL MATCH!!!

See also my https://github.com/HakkaTjakka/PROJECT-CGI-BTE121-LEAFLET/blob/main/xampp/apache/conf/def.conf configuration on directory aliases.
Otherwise they must be placed in the htdocs directory in xampp and pointed to there.

So you need the (so far) 11 directories created from the program REGION_FINDER (readme.md),
the Leaflet part with the webserver files (readme.md), the xampp configuration and cgi-bin part, all in the right places.
If you use own world region x/z coords, you will have to locate the corresponting latlng parameters for the index.html Javascript part for Leaflet.
You need to look at the data on the tiles like r.x.z.mca. Then you get the latlng coords by clicking right mouse key, and you can plug them into the index.html.

What does the the cgi do now?

It calls the project.exe file, that will output the binary data for the tile that is shown.
The source are the directorys from the REGION_FINDER repo (1-18) containing the x/z sorted tiles of the minecraft world, in this case whole holland bte121 projection.
You can create the tiles with the https://github.com/HakkaTjakka/MinecraftWorldEditor repo, with the command from pacman_cuberite (path set correct to pacman_cuberite/bin dir):

pacman.exe plot

where your minecraft world should be in /saves/test/region/done0, and/or done-1, done-2, done1, done2 for floors, for the Cubic Chunks format.
These dirs are used when converting the raw Google 3D Earth data into r.x.z.mca files. 
They can be stacked to Cubic Chunks with the https://github.com/HakkaTjakka/sample-utrecht/blob/main/CONVERTOR.rar
Note: the region_finder in the https://github.com/HakkaTjakka/sample-utrecht/tree/main/region-finder repo is a somehow previous version of functions for dealing r.x.y.mca files for a region map

For now the maximum zoomlevel is 11, where the r.x.z.mca region tiles are scale 1:1, meaning every square equals one region file.
Reason for this: Converting the scale 1:1 level 11 tiles up into 4 for higher zoomlevel, because Leaflet doesnt zoom them, i can not find the right parameters in index.html for that.

Also: You can change all tiles at will with like sfml image / texture / shaders stuff, so you can deliver real time graphics from sfml including shaders
and stuff, to display into a map. The c/c++ part can generate a map on several zoom levels, without needing textures from harddrive as files.
You could make a shader creating tiles on some zoomlevel, and blow the shader up when zooming in, or make the perspective different.

Hereby you have a cgi-bin interface to a c/c++ executable residing on the server site, able of generating ALL code the webserver has to supply to the client.
You can gererate all you data, even multimedia stuff right from the server from a .exe file.

This is just the first attempt and meant to get oversight on Build The Earth 121 Minecraft 1.12.2 data, region files, coordinates in Minecraft space, 
coordinates in map space, and/or lat/lng (gps) space. 
You can create c/c++ code creating maps and / or other stuff with pictures for displaying into the web browser.

Lots of thing come together here. The server (xampp) cgi-bin interface, the c/c++ .exe outputting all the data requested from the webpage by cgi-bin parameters,
the Leaflet script for showing zoomable map tiles, the MinecraftWorldEditor program for making a top view images of the region files of a world, 
Google Earth 3d data downloaded with the Node.js script from the MinecraftWorldEditor repo (earth), converted to voxels, etc.

Possible: Using GPU shaders for showing only the parts of it that will show up in the tiles. Therefore only the (zoomed in, real time generated gpu shader output)

I know the repo(s) are not organized. Its called 'junk code'.
But the 'junk' works, in right configurated. 
displayed area will be rendered. 
The project.exe now converts the .png files from the REGION_FILES to .jpg with SFML functions. And places them into the cgi-bin dir.
Then, when needed again they don't have to be converted. Its meant for bandwith/speed, but also for creating images on the fly and displaying them in a website.

Of course if you have some fantasy this/these repo(s) can do much more on interactive stuff on cgi-bin, sfml, c/c++, html, and javascript.
The interfacing combinations / possibilities are endless. 
You can use the website html/Javascript to do things, but also the cgi-bin c/c++ program. 
You could write a project.exe file that records or shows (graphical) real time webserver data on the server site, but also send real time generated graphic output to the client.
Wich can by ANYTHING that you can send over the web. You have a c/c++ html/Javascript/content generator interacting with the website in real time.

If you need help (then things go very quick) msg me plz. I'm gladly willing to help and ask (Minecraft fans) to join this project(s).


