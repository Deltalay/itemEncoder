/*******************************************************************************
MIT License

Copyright (c) 2024 Deltalay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <iomanip>
#include "json.hpp"
#define SECRET "PBG892FXX982ABC*"
using namespace std;
using json = nlohmann::json;
int getFilesize(string name)
{
  ifstream file(name, std::ios::ate | std::ios::binary);
  return file.tellg();
}
string encodename(string name, int id)
{
  string secret = SECRET;
  int secretLen = secret.length();
  int len = name.length();
  string output;
  for (int i = 0; i < len; i++)
  {
    int charpos = (i + id) % secretLen;
    char secretchar = secret[charpos];
    output += name[i] ^ secretchar;
  }
  return output;
}
int main()
{
  ifstream file("data.json");
  json jf;
  file >> jf;
  size_t size = getFilesize("data.json");
  if (size == -1)
  {
    cout << "Please make sure that items.json is in the same directory!" << endl;
    return 0;
  }
  ofstream dat("items.dat", ios::binary);
  uint32_t pos = 0;
  uint8_t *data = static_cast<uint8_t *>(malloc(size));
  auto write_string = [&](const std::string &str)
  {
    uint16_t strsize = static_cast<uint16_t>(str.size());
    memcpy(data + pos, &strsize, 2);
    pos += 2;
    for (int i = 0; i < strsize; ++i)
      data[pos++] = static_cast<uint8_t>(str[i]);
  };
  memset(data, 0, size);
  int16_t item_version = jf["itemsdatVersion"];
  int item_count = jf["itemCount"];
  memcpy(data + pos, &item_version, 2);
  memcpy(data + pos + 2, &item_count, 4);
  pos += 6;
  for (int i = 0; i < item_count; i++)
  {
    int32_t id = jf["items"][i]["itemID"];
    string texture = jf["items"][i]["texture"];
    memcpy(data + pos, &id, 4);
    pos += 4;
    string name = jf["items"][i]["name"];
    cout << "Encode: " + name + ", ID: " + to_string(i) << endl;
    int8_t m_item_category = jf["items"][i]["itemCategory"];
    uint8_t m_editable_type = jf["items"][i]["editableType"];
    memcpy(data + pos, &m_editable_type, 1);
    pos += 1;
    memcpy(data + pos, &m_item_category, 1);
    pos += 1;
    int actionType = jf["items"][i]["actionType"];
    memcpy(data + pos, &actionType, 1);
    pos += 1;
    int hitSoundType = jf["items"][i]["hitSoundType"];
    memcpy(data + pos, &hitSoundType, 1);
    pos += 1;
    write_string(encodename(name, id));
    write_string(texture);
    int textureHash = jf["items"][i]["textureHash"];
    memcpy(data + pos, &textureHash, 4);
    pos += 4;
    int itemKind = jf["items"][i]["itemKind"];
    memcpy(data + pos, &itemKind, 1);
    pos += 1;
    int val1 = jf["items"][i]["val1"];
    memcpy(data + pos, &val1, 4);
    pos += 4;
    int texturex = jf["items"][i]["textureX"];
    int texturey = jf["items"][i]["textureY"];
    memcpy(data + pos, &texturex, 1);
    pos += 1;
    memcpy(data + pos, &texturey, 1);
    pos += 1;
    short spread_type = jf["items"][i]["spreadType"];
    memcpy(data + pos, &spread_type, 1);
    pos += 1;
    int isStripeyWallpaper = jf["items"][i]["isStripeyWallpaper"];
    memcpy(data + pos, &isStripeyWallpaper, 1);
    pos += 1;
    short collisionType = jf["items"][i]["collisionType"];
    memcpy(data + pos, &collisionType, 1);
    pos += 1;
    int breakHits = jf["items"][i]["breakHits"];
    memcpy(data + pos, &breakHits, 1);
    pos += 1;
    int dropChance = jf["items"][i]["dropChance"];
    memcpy(data + pos, &dropChance, 4);
    pos += 4;
    int clothingType = jf["items"][i]["clothingType"];
    memcpy(data + pos, &clothingType, 1);
    pos += 1;
    int rarity = jf["items"][i]["rarity"];
    memcpy(data + pos, &rarity, 2);
    pos += 2;
    int maxAmount = jf["items"][i]["maxAmount"];
    memcpy(data + pos, &maxAmount, 1);
    pos += 1;
    string extraFile = jf["items"][i]["extraFile"];
    write_string(extraFile);
    int extraFileHash = jf["items"][i]["extraFileHash"];
    memcpy(data + pos, &extraFileHash, 4);
    pos += 4;
    int audioVolume = jf["items"][i]["audioVolume"];
    memcpy(data + pos, &audioVolume, 4);
    pos += 4;
    string petName = jf["items"][i]["petName"];
    string petPrefix = jf["items"][i]["petPrefix"];
    string petSuffix = jf["items"][i]["petSuffix"];
    string petAbility = jf["items"][i]["petAbility"];
    write_string(petName);
    write_string(petPrefix);
    write_string(petSuffix);
    write_string(petAbility);
    int seedBase = jf["items"][i]["seedBase"];
    int seedOverlay = jf["items"][i]["seedOverlay"];
    int treeBase = jf["items"][i]["treeBase"];
    int treeLeaves = jf["items"][i]["treeLeaves"];
    int seedColor = jf["items"][i]["seedColor"];
    memcpy(data + pos, &seedBase, 1);
    pos += 1;
    memcpy(data + pos, &seedOverlay, 1);
    pos += 1;
    memcpy(data + pos, &treeBase, 1);
    pos += 1;
    memcpy(data + pos, &treeLeaves, 1);
    pos += 1;
    memcpy(data + pos, &seedColor, 4);
    pos += 4;
    int seedOverlayColor = jf["items"][i]["seedOverlayColor"];
    memcpy(data + pos, &seedOverlayColor, 4);
    pos += 4;
    uint32_t m_ingredient = 0;
    memcpy(data + pos, &m_ingredient, 4);
    pos += 4;
    int growTime = jf["items"][i]["growTime"];
    memcpy(data + pos, &growTime, 4);
    pos += 4;
    int val2 = jf["items"][i]["val2"];
    memcpy(data + pos, &val2, 2);
    pos += 2;
    short isRayman = jf["items"][i]["isRayman"];
    memcpy(data + pos, &isRayman, 2);
    pos += 2;
    string extraOptions = jf["items"][i]["extraOptions"];
    string texture2 = jf["items"][i]["texture2"];
    string extraOptions2 = jf["items"][i]["extraOptions2"];
    write_string(extraOptions);
    write_string(texture2);
    write_string(extraOptions2);
    uint8_t m_reserved[80] = {0};
    memcpy(data + pos, m_reserved, 80);
    pos += 80;
    string punchOptions = jf["items"][i]["punchOptions"];
    if (item_version >= 11)
    {
      write_string(punchOptions);
    }
    if (item_version >= 12)
    {
      pos += 13;
    }
    if (item_version >= 13)
    {

      pos += 4;
    }
    if (item_version >= 14)
    {
      pos += 4;
    }
    if (item_version >= 15) {
      pos += 25;
      int16_t strLen = *(int16_t *)&data[pos];
      pos += 2 + strLen;
    }
  }
  dat.write(reinterpret_cast<char *>(data), pos);
  dat.close();
  free(data);
  cout << "Encode successfully!" << endl;
  return 0;
}
