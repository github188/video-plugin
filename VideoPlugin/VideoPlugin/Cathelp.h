#include "comcat.h"
#pragma once

// Helper function to create a component category and associated
// description
HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription);

// Helper function to register a CLSID as belonging to a component
// category
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);

HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid);
