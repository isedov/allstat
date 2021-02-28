#define _CRT_NONSTDC_NO_DEPRECATE
#include <AllStat/AllStat.h>
#include "AllStatDefs.h"

#include <cassert>
#include <string.h>

using namespace AllStat;

#pragma warning(disable : 4996 26812)

void LRESULTGetTables(TABLES& t);

std::string AllStat::Winerr2Str(uint32_t lr)
{
  TABLES t;
  LRESULTGetTables(t);

  const STATUS_ITEM* p = EntryByCode(lr, t.Items, t.Code2name);
  return FormatName(lr, p, "0x%08X");
}

const char* Winerr2StrC(uint32_t value)
{
  std::string str = Winerr2Str(value);
  return strdup(str.c_str());
}

ItemArray AllStat::WinerrInfo(uint32_t lr)
{
  TABLES t;
  LRESULTGetTables(t);

  ItemArray aa;
  auto a = EntryByCodeArray(lr, t.Items, t.Code2name);
  for (auto it = a.begin(); it != a.end(); ++it)
  {
    auto item = *it;

    AS_ITEM ai;
    ItemFromStatusItem(*item, ai, AS_GENERATOR::AS_LRESULT, AS_GENERATOR::AS_LRESULT);

    aa.push_back(ai);
  }
  return aa;
}

AS_API PAS_ITEM_ARRAY WinerrInfoC(uint32_t e)
{
  ItemArray arr = WinerrInfo(e);
  return BuildItemArray(arr);
}

const char* Winerr2Name(uint32_t lr)
{
  TABLES t;
  LRESULTGetTables(t);

  const STATUS_ITEM* p = EntryByCode(lr, t.Items, t.Code2name);
  return p ? p->Name : nullptr;
}

uint32_t Name2WinerrItem(const char* constant_name, PAS_ITEM pitem)
{
  if (pitem == nullptr)
  {
    assert(pitem);
    return AS_UNKNOWN;
  }

  TABLES t;
  LRESULTGetTables(t);

  auto e = EntryByName(constant_name, t.Items, t.Name2code);
  if (e == nullptr)
    return AS_UNKNOWN;

  ItemFromStatusItem(*e, *pitem, AS_GENERATOR::AS_LRESULT, AS_GENERATOR::AS_LRESULT);
  return 0;
}
