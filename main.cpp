#include "tokenize_parse.h"
#include "get_artistid.h"
#include "genres.h"
#include <cpr/cpr.h>

//token from spotify.
const string TOKEN = "BQB-nw9dNNhXh3Yi0wxitlW-BBQPjVEi5rXoVsgsV4S_tSBIY5Tql08D2DfnANTumS9wuKtAfeJSlpRc-uLrosD8Df0Pn1BIOAxx_QkJfV86HCBzt0-HTAfI6ECDDgE9pWNcZByUfBOr8O1723GmWtveMohS3C1SCYDkH7grlrSk6UOcq3WOowWWFVbvajlMCWMfKCJItoPliBlU2nxvVyUxe2MOZObtoebexs0dupnY1Xhtt46UrW4bwmHa5osi0gDGimx7Yg";

//call a new api with returned unique id.
void callAPI_withID(string id) {

    string URI = "https://api.spotify.com/v1/artists/";
    URI = URI + id;
    cpr::Response k = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    cout << "Status code: " << k.status_code << endl;

    auto genres = getgenres(k.text);
    for (auto x : genres) {
        cout << x << endl;
    }
}

//call spotify api with trackname and artist name (3rd question)
void callAPI_artistname(string artistName) {
    
    string URI = "https://api.spotify.com/v1/search?q=";
    URI = URI + parseName(artistName);
    URI = URI + "&type=artist&limit=1";

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });

    cout << "Status code: " << r.status_code << '\n';
    
    string id = getartistid(r.text);
    callAPI_withID(id);

}

int main(int argc, char** argv) {
    cout << "Testing...." << std::endl;
    //string track = "morrow";
    string artistName = "070 shake";
    callAPI_artistname(artistName);
    //Genre_Matchup();
    return 0;
}