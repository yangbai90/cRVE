#include "GmshIO.h"

int GmshIO::GetNodesNumViaElmtType(int elmttype) const
{
    switch(elmttype)
    {
        case 1:
            // 2-node line
            return 2;
        case 2:
            // 3-node triangle
            return 3;
        case 3:
            // 4-node quadrangle
            return 4;
        case 4:
            // 4-node tetrahedron
            return 4;
        case 5:
            // 8-node hexahedron
            return 8;
        case 6:
            // 6-node prism
            return 6;
        case 7:
            // 5-node pyramid
            return 7;
        case 8:
            //3-node second order line
            return 3;
        case 9:
            // 6-node second order triangle
            return 6;
        case 10:
            // 9-node second order quadrangle
            return 9;
        case 11:
            // 10-node second order tetrahedron
            return 10;
        case 12:
            // 27-node second order hexahedron
            return 27;
        case 13:
            // 18-node second order prism
            return 18;
        case 14:
            // 14-node second order pyramid
            return 14;
        case 15:
            // 1-node point
            return 1;
        case 16:
            // 8-node second order quadrangle
            return 8;
        case 17:
            // 20-node second order hexahedron
            return 20;
        case 18:
            // 15-node second order prism
            return 15;
        case 19:
            // 13-node second order pyramid
            return 13;
        case 20:
            // 9-node third order incomplete triangle
            return 9;
        case 21:
            // 10-node third order triangle
            return 10;
        case 22:
            // 12-node fourth order incomplete triangle
            return 12;
        case 23:
            // 15-node fourth order triangle
            return 15;
        case 24:
            // 15-node fifth order incomplete triangle
            return 15;
        case 25:
            // 21-node fifth order complete triangle
            return 21;
        case 26:
            // 4-node third order edge
            return 4;
        case 27:
            // 5-node fourth order edge
            return 5;
        case 28:
            // 6-node fifth order edge
            return 6;
        case 29:
            // 20-node third order tetrahedron
            return 20;
        case 30:
            // 35-node fourth order tetrahedron
            return 35;
        case 31:
            // 56-node fifth order tetrahedron
            return 56;
        case 92:
            // 64-node third order hexahedron
            return 64;
        case 93:
            // 125-node fourth order hexahedron
            return 125;
        default:
            return -1;

    }
}

//*********************************************************
int GmshIO::GetElmtDimViaElmtType(int elmttype) const
{
    switch(elmttype)
    {
        case 1:
            // 2-node line
            return 1;
        case 2:
            // 3-node triangle
            return 2;
        case 3:
            // 4-node quadrangle
            return 2;
        case 4:
            // 4-node tetrahedron
            return 3;
        case 5:
            // 8-node hexahedron
            return 3;
        case 6:
            // 6-node prism
            return 3;
        case 7:
            // 5-node pyramid
            return 3;
        case 8:
            //3-node second order line
            return 1;
        case 9:
            // 6-node second order triangle
            return 2;
        case 10:
            // 9-node second order quadrangle
            return 2;
        case 11:
            // 10-node second order tetrahedron
            return 3;
        case 12:
            // 27-node second order hexahedron
            return 3;
        case 13:
            // 18-node second order prism
            return 3;
        case 14:
            // 14-node second order pyramid
            return 3;
        case 15:
            // 1-node point
            return 0;
        case 16:
            // 8-node second order quadrangle
            return 2;
        case 17:
            // 20-node second order hexahedron
            return 3;
        case 18:
            // 15-node second order prism
            return 3;
        case 19:
            // 13-node second order pyramid
            return 3;
        case 20:
            // 9-node third order incomplete triangle
            return 2;
        case 21:
            // 10-node third order triangle
            return 2;
        case 22:
            // 12-node fourth order incomplete triangle
            return 2;
        case 23:
            // 15-node fourth order triangle
            return 2;
        case 24:
            // 15-node fifth order incomplete triangle
            return 2;
        case 25:
            // 21-node fifth order complete triangle
            return 2;
        case 26:
            // 4-node third order edge
            return 1;
        case 27:
            // 5-node fourth order edge
            return 1;
        case 28:
            // 6-node fifth order edge
            return 1;
        case 29:
            // 20-node third order tetrahedron
            return 3;
        case 30:
            // 35-node fourth order tetrahedron
            return 3;
        case 31:
            // 56-node fifth order tetrahedron
            return 3;
        case 92:
            // 64-node third order hexahedron
            return 3;
        case 93:
            // 125-node fourth order hexahedron
            return 3;
        default:
            return -1;

    }
}

//*******************************************************
//*********************************************************
string GmshIO::GetElmtNameViaElmtType(int elmttype) const
{
    switch(elmttype)
    {
        case 1:
            // 2-node line
            return "edge";
        case 2:
            // 3-node triangle
            return "triangle";
        case 3:
            // 4-node quadrangle
            return "quadrangle";
        case 4:
            // 4-node tetrahedron
            return "tetrahedron";
        case 5:
            // 8-node hexahedron
            return "hexahedron";
        case 6:
            // 6-node prism
            return "prism";
        case 7:
            // 5-node pyramid
            return "pyramid";
        case 8:
            //3-node second order line
            return "edge";
        case 9:
            // 6-node second order triangle
            return "triangle";
        case 10:
            // 9-node second order quadrangle
            return "quadrangle";
        case 11:
            // 10-node second order tetrahedron
            return "tetrahedron";
        case 12:
            // 27-node second order hexahedron
            return "hexahedron";
        case 13:
            // 18-node second order prism
            return "prism";
        case 14:
            // 14-node second order pyramid
            return "pyramid";
        case 15:
            // 1-node point
            return "point";
        case 16:
            // 8-node second order quadrangle
            return "quadrangle";
        case 17:
            // 20-node second order hexahedron
            return "hexahedron";
        case 18:
            // 15-node second order prism
            return "prism";
        case 19:
            // 13-node second order pyramid
            return "pyramid";
        case 20:
            // 9-node third order incomplete triangle
            return "triangle";
        case 21:
            // 10-node third order triangle
            return "triangle";
        case 22:
            // 12-node fourth order incomplete triangle
            return "triangle";
        case 23:
            // 15-node fourth order triangle
            return "triangle";
        case 24:
            // 15-node fifth order incomplete triangle
            return "triangle";
        case 25:
            // 21-node fifth order complete triangle
            return "triangle";
        case 26:
            // 4-node third order edge
            return "edge";
        case 27:
            // 5-node fourth order edge
            return "edge";
        case 28:
            // 6-node fifth order edge
            return "edge";
        case 29:
            // 20-node third order tetrahedron
            return "tetrahedron";
        case 30:
            // 35-node fourth order tetrahedron
            return "tetrahedron";
        case 31:
            // 56-node fifth order tetrahedron
            return "tetrahedron";
        case 92:
            // 64-node third order hexahedron
            return "hexahedron";
        case 93:
            // 125-node fourth order hexahedron
            return "hexahedron";
        default:
            return "unknown";

    }
}
