#!/usr/bin/python3

# print("siema")


API_KEY = "a4c7378a-5798-40f6-a9c1-6a0fae8c4da4"
MACZKA_ID = "1474"
# URL = "api.um.warszawa.pl/api/action/dbtimetable_get/?id=b27f4c17-5c50-4a5b-89dd-236b282bc499&name=Maczka&apikey="



URL = "https://api.um.warszawa.pl/api/action/dbtimetable_get?id=e923fa0e-d96c-43f9-ae6e-60518c9f3238&busstopId=%s&busstopNr=01&line=245&apikey=%s" % (MACZKA_ID, API_KEY)


import urllib.request
import urllib.parse

f = urllib.request.urlopen(URL)
print(f.read().decode('utf-8'))


