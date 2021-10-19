#include <SFML\Graphics.hpp>
#include <cassert>

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

void log(std::string tolog) {
    static FILE* out=fopen("texture.log","a");
    if (tolog=="close") {
        fclose(out);
        exit(0);
    }
    fputs(tolog.c_str(),out);
}


char evars[20][80]={"SERVER_SOFTWARE", "SERVER_NAME", "SERVER_PROTOCOL",
                    "SERVER_PORT",
                    "GATEWAY_INTERFACE", "REQUEST_METHOD",
                    "PATH_INFO", "PATH_TRANSLATED", "SCRIPT_NAME",
                    "QUERY_STRING",
                    "REMOTE_HOST", "REMOTE_ADDR", "REMOTE_USER",
                    "REMOTE_IDENT",
                    "AUTH_TYPE", "CONTENT_TYPE", "CONTENT_LENGTH",
                    "HTTP_ACCEPT", "HTTP_USER_AGENT", "HTTP_REFERER"};


int evar(void) {
  const int numvars=20;
  int i;

  printf("Content-type: text/plain\n\n");
  for (i=0;i<numvars;i++) printf("%s = %s\n", evars[i], getenv(evars[i]));
  return 0;
}

static std::string GetFileName(const std::string& filepath)
{
    if (filepath.find_last_of("/\\") != std::string::npos)
        return filepath.substr(1+filepath.find_last_of("/\\"),filepath.length());
    return "";
}

static std::string GetBaseDir(const std::string& filepath)
{
    if (filepath.find_last_of("/\\") != std::string::npos)
        return filepath.substr(0, filepath.find_last_of("/\\"));
    return "";
}

struct stat stat_buffer;

bool file_exists(const char * filename)
{
    int exist = stat(filename,&stat_buffer);
    if (exist==0) return true;
    return false;
}

int PNG() {
    srand(time(0));
    _setmode( _fileno( stdout ), _O_BINARY );   //cuckoo's
    char* save_env = getenv("QUERY_STRING");   /* get environment variable */
    char env_value[strlen(save_env) + 1];
    if (strlen(env_value) == 0) {
        log(std::string() + "=empty\n");
        exit (2);
    }
    strcpy(env_value, save_env);    /* save environment variable */
    log(std::string() + env_value + "\n");

    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;

    std::string fn=std::string() + "F:/REGION_FINDER/" + env_value;
//    std::string fn=std::string() + "F:/PROJECT/" + env_value;
//    std::string fn=std::string() + "G:/WEB/NL/" + env_value;

    pFile = fopen ( fn.c_str(), "rb" );
    if (pFile!=NULL) {
        if ((strstr(fn.c_str(), ".jpg")) == NULL) {
            fclose(pFile);
            std::string fn_file=GetFileName(fn);
            if (fn_file.find_last_of(".") != std::string::npos) fn_file=fn_file.substr(0,fn_file.find_last_of("."))+".jpg";
//index.html:   return "http://83.83.222.154/cgi-bin/texture.cgi?" + coords.z + "/" + mc_x + "/" + mc_y + "/r." + coords.x + "." + coords.y + ".png";
//            log(fn + "\n");
            std::string zoom=GetBaseDir(fn); //y dir
//            log(zoom + "\n");
            zoom=GetBaseDir(zoom); //x dir
//            log(zoom + "\n");
            zoom=GetBaseDir(zoom); //zoomfactor dir
//            log(zoom + "\n");
            zoom=GetFileName(zoom);
//            log(zoom + "\n");
            if (!file_exists(zoom.c_str())) mkdir(zoom.c_str());
            fn_file=zoom+'/'+fn_file;
            log(fn_file + "\n");
            pFile = fopen ( fn_file.c_str(), "rb" );
            if (pFile==NULL) {
                sf::Image m_image;
                log("Loading: " + fn + "\n");
                if (m_image.loadFromFile(fn.c_str())==true) {
                    fn=fn_file;
                    m_image.saveToFile(fn.c_str());
                } else {
                    fn=std::string() + "F:/NL_TILE_MAP/skull_usd.jpg";
                }
                pFile = fopen ( fn.c_str(), "rb" );
            }
        } //else {
//            fclose(pFile);
//            std::string fn_file=GetFileName(fn);
//            if (fn_file.find_last_of(".") != std::string::npos) fn_file=fn_file.substr(0,fn_file.find_last_of("."))+".jpg";
//            fn=fn_file;
//            pFile = fopen ( fn.c_str(), "rb" );
//        }
    }

    if (pFile==NULL) {
        log(std::string() + "Can not open: " + fn + "\n");
        fn=std::string() + "F:/NL_TILE_MAP/skull.jpg";
        pFile = fopen ( fn.c_str(), "rb" );
        if (pFile==NULL) {
            log(std::string() + "echo Can not open: " + fn + "\n");
            exit (1);
        }
    }

    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    log(fn + " Size: "+to_string(lSize) + "\n") ;

    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {
        fclose(pFile);
        log(std::string() + "echo Buffer==NULL: " + fn + "\n");
        exit (1);
    }

//    log("Reading. ") ;
    result = fread (buffer,1,lSize,pFile);
//    log("Ready reading. Read: " + to_string(result) + " bytes.\n");
    fclose (pFile);
    if (result != lSize) {
        log("echo Buffer wrong size. " + to_string(result) + "!=" + to_string(lSize) + " : " + fn + "\n");
        exit (1);
    }

//    log(std::string() + "Writing buffer to stdout.\n");
//    printf("Content-type: image/jpeg\n\n");

    std::string html;
    if ((strstr(fn.c_str(), ".png")) != NULL) {
        html = "Content-Type: image/png; Content-Transfer-Encoding: binary; Content-Length: " + to_string(lSize) + ";charset=ISO-8859-4 \r\n\r\n";
    } else if ((strstr(fn.c_str(), ".jpg")) != NULL) {
        html =  std::string() + "Content-Type: image/jpg;" +
                "Content-Transfer-Encoding: binary; Content-Length: " + to_string(lSize) + ";" +
                "charset=ISO-8859-4;" +
                "\r\n\r\n";
    } else if ((strstr(fn.c_str(), ".jpeg")) != NULL) {
        html =  std::string() + "Content-Type: image/jpeg;" +
                "Content-Transfer-Encoding: binary; Content-Length: " + to_string(lSize) + ";" +
                "\r\n\r\n";
    }
    printf(html.c_str());
    result = fwrite(buffer,1,lSize,stdout);
    //std::cout.write(buffer, lSize);

//    log("Ready writing. Written: " + to_string(result) + " bytes.\n");
    //puts(buffer);

//    log("done. fflush(stdout); ");
//    printf("\r\n");
    fflush(stdout);
//    log("Flushed.\n");

//    log(std::string() + "Writing to file: " + env_value + "\n");
//    pFile = fopen ( env_value, "wb" );
//    result = fwrite(buffer,1,lSize,pFile);
//    log("Ready writing. Written: " + to_string(result) + " bytes.\n");
//    fclose(pFile);

    free (buffer);

    exit (0);
}

int web2 ()
{
   char *env_value;
   char *save_env;
   time_t current_time;

   printf("Content-type: text/html\n\n");
    printf("<html><head><title></title></head><body>");
   printf("C Program Version\n");
   current_time = time(NULL);                       /* get current time */
   printf("It is now %s\n", ctime(&current_time));
   save_env = getenv("QUERY_STRING");   /* get environment variable */
   env_value = (char*) malloc((size_t)strlen(save_env) + 1);
   if (env_value == NULL)
   {
      printf("Major failure; please notify the webmaster\n");
      exit (2);
   }
   strcpy(env_value, save_env);    /* save environment variable */
    printf("The query is %s\n", env_value);          /* and print it */
   printf("You are signed onto %s\n", getenv("REMOTE_HOST"));
   printf("Your IP Address is %s\n", getenv("REMOTE_ADDR"));
   fflush(stdout);              /* force physical write */
   exit (0);
}

int web() {
    char *tmpStr;
    char *user;
    printf("Content-Type:text/html\n\n");
    printf("<html><head><title></title></head><body>");
    tmpStr = getenv("QUERY_STRING");
    //while(*tmpStr && *tmpStr != '=') tmpStr++;
      //  user = tmpStr+1,
        user = tmpStr;
    printf("Adding %s to  User Database",user);
    //system("wget http://localhost:8000/newuser/");//call script to add user?
    printf("</body></html>");
    return 0;//return user?
}


int main() {
//    evar();
//    exit(0);
    PNG();
    exit(0);

    sf::RenderWindow sfmlWin(sf::VideoMode(600, 360), "Hello World SFML Window");
    sf::Font font;
    //You need to pass the font file location
    if (!font.loadFromFile(/*Put the filename that identify the font file you want to load*/
        "fonts/impact.ttf")) {
        return -1;
    }
    sf::Text message("Hello, World !", font);

    while (sfmlWin.isOpen()) {

        sf::Event e;
        while (sfmlWin.pollEvent(e)) {

            switch (e.type) {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
            }
        }

        sfmlWin.clear();
        sfmlWin.draw(message);
        sfmlWin.display();
    }
    return 0;
}

