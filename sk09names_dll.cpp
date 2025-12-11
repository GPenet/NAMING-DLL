
/*
My standard start using maingp as command line analyser
contains the entry G0() called by main
*/
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <utility>
#include <limits.h>
#include <stdlib.h>
#include <sys/timeb.h>
using namespace std;
// nothing to do here
#include "maingp_user.h"
#include "sk0\sk0_cpp_lookup.h"
#include "dllusers\u05skvcar_user.h"
#include "dllusers\u06skbf_user.h"
#include "dllusers\skgrid_minlex_user.h"
//===================================================== 6 bit  <=>  char
/* ascii values
0-9		48-57		0-9
A-Z		65-90		10-35
a-z		97-122		36-61
{}    123-125       62-63
*/

const char* bit6 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz{}";
//                  1234567890123456789012345678901234567890123456789012345678901234
int Get6Bits(int i, char* bf14) {
	register int v = bf14[i];
	if (v >= 97 && v <= 123)v -= 61; // a z (
	else if (v >= 65 && v <= 90)v -= 55; // A Z
	else if (v >= 48 && v <= 57)v -= 48; // 0-9
	else if (v == 125) v = 63; // ) 
	else v = 0; // not valid put to empty
	return v;
}
void PuzzleInBitField(char* puz, char* d) {
	// d is 14*6=84 bits in 14 char
	for (int i = 0, k = 0; i < 14; i++) {
		register int v = 0;
		for (int j = 0; j < 6; j++, k++) {
			if (puz[k] != '.')v |= 1 << j;
			d[i] = bit6[v];
			if (k == 80) break;
		}
	}
}

//======================================== naming exchange area
struct NAMESII{
	char edp[82];// ed puz string mode 
	char n25[26];// name 25 bytes string mode
	char n19[20];// name 19 bytes string mode
	char n14[15];// bitf 81 14 bytes string mode
	uint64_t rank;// sol rank 1 - 5 472 730 538 (0 no rank)
	inline void Init() {memset(this, 0, sizeof NAMESII);}
	inline void Convertto19( ) {
		register uint64_t r = rank, r2;
		{
			r2 = (r >> 27) & 0x3f; n19[0] = bit6[r2];//  highest bits
			r2 = (r >> 21) & 0x3f; n19[1] = bit6[r2];
			r2 = (r >> 15) & 0x3f; n19[2] = bit6[r2];
			r2 = (r >> 9) & 0x3f; n19[3] = bit6[r2];
			r2 = (r >> 3) & 0x3f; n19[4] = bit6[r2];
		}
		register int rx = (int)r & 7;// last 3  bits
		for (int i = 0; i < 14; i++) {
			register int ry = Get6Bits(i, n14);
			rx = (rx << 3) | ry & 7;
			n19[i + 5] = bit6[rx];
			rx = ry >> 3;
		}
	}

}mywi;


//====================================================== entries   
extern "C" __declspec(dllexport) NAMESII* SknameGetP(); // init and get exchange area pointer
extern "C" __declspec(dllexport) int SknamePuz(char* p); // puz to name back 1 if fail
extern "C" __declspec(dllexport) int Skname25to19(char* z);
extern "C" __declspec(dllexport) int Skname25topuz(char* z);
extern "C" __declspec(dllexport) int Skname19to25(char* z, int edpuz);


NAMESII* SknameGetP(	){// get needed pointers and return my pointer
	ptpgc = SkbsSetModeWithAutos();
	pzhe = SkbfGetZhePointer();
	if (SkvcatSetModeGetVCDESK(2, &pvcdesc)) return 0; 
	mywi.Init();
	memcpy(mywi.edp, "hello", 5);
	return & mywi;}



void Expand14to81(char* puz, char* bf14, char * sol) {
	int k = 0;
	for (int i = 0, k = 0; i < 14; i++) {// 6 bits to expand
		register int v = Get6Bits(i,bf14); 
		int nd = (i == 13) ? 3 : 6;
		for (int j = 0; j < nd; j++,v>>=1,k++) {
			if (v & 1)puz[k] = sol[k] ;
			else puz[k] = '.';
		}
	}
}
int  Expand14toBF128(BF128& d,char* bf14) {
	int k = 0,n=0;
	d.SetAll_0();
	for (int i = 0, k = 0; i < 14; i++) {// 6 bits to expand
		register int v = Get6Bits(i, bf14);
		int nd = (i == 13) ? 3 : 6;
		for (int j = 0; j < nd; j++, v >>= 1, k++) {
			if (v & 1) {d.Set_c(k); n++;}			
		}
	}
	return n;
}

inline char * R_toR10(int64_t r) {// put rank in string 10 leading blank
	static char  ws[11];
	memset(ws, ' ', 10); ws[10] = 0;
	if (r > 5472730538) { ws[9] = '0'; return ws; }//5,472,730,538 ED?
	register uint64_t R = r,W,X;
	int i = 9;
	while (R > 0) {	W = R; R /= 10; X = W - 10 * R;	ws[i--] = (char)(X + '0');	}
	return ws;
}

inline void Convertto19zz(uint64_t rank,char * zeb, char* z19) {
	register uint64_t r = rank, r2;
	{
		r2 = (r >> 27) & 0x3f; z19[0] = bit6[r2];//  highest bits
		r2 = (r >> 21) & 0x3f; z19[1] = bit6[r2];
		r2 = (r >> 15) & 0x3f; z19[2] = bit6[r2];
		r2 = (r >> 9) & 0x3f; z19[3] = bit6[r2];
		r2 = (r >> 3) & 0x3f; z19[4] = bit6[r2];
	}
	register int rx = (int)r & 7;// last 3  bits
	for (int i = 0; i < 14; i++) {
		register int ry = Get6Bits(i, zeb);
		rx = (rx << 3) | ry & 7;
		z19[i + 5] = bit6[rx];
		rx = ry >> 3;
	}
}
int IsNotValidCallRB(char * ze) {
	if (strlen(ze) < 15)return 1;// no empty line
	int i = 0;
	if (ze[10] == ' ') i = 10;// fix length for r
	else for (; i < 15; i++)if (ze[i] == ';') break;
	if (i > 10)  return 1;
	char* zeb = &ze[i + 1];
	int ll = (int)strlen(zeb);	if (ll != 14) return 1;
	memcpy(mywi.n14, zeb, 14);
	ze[i] = 0;	mywi.rank = strtoll(ze, 0, 10);
	if (mywi.rank < 1) return 1;
	if (mywi.rank > 5472730538) return 1;
	return 0;
}
int GetEDpuz() {// in shared area after rank + bit field ok
	char solc[82]; // grid in char mode
	if (SkvcatFinSolForRank(mywi.rank) < 0) return 1;//  should never be
	else memcpy(solc, pvcdesc->g.b1, 81);
	Expand14to81(mywi.edp, mywi.n14, solc);// now puzzle wp
	return 0;
}
//===================================================== processes
int SknamePuz(char* p) {
	mywi.Init();
	if (strlen(p) < 81)return 1;
	int ncell = 0;
	for (int i = 0; i < 81; i++) {
		char c = p[i];		if (c == '.') continue;
		if (c > '0' && c <= '9') { ncell++; continue; }		
		return 1;// not valid format
	}
	if (ncell < 17)  return 1; // can't be valid puzzle
	if (SkbfCheckValidityQuick(p) != 1)  return 1; // not a valid puzzle
	memcpy(mywi.n19, "valid", 5);
	int* vv = pzhe->gsol,smin[81];
	char  zem2[82];  zem2[81] = 0;
	SkbsGetMin(vv, smin);

	if(!(mywi.rank = SkvcatGetRankFromSolMin(smin))) return 1;// should never be
	memcpy(mywi.n19, "rankok", 6);
	GRIDPERM wgperm;
	char* pbase = ptpgc->t[0];
	wgperm.Import19(vv, pbase);
	wgperm.MorphPuzzle(p,mywi.edp);
	memcpy(mywi.n19, "edpok", 6);
	for (int i = 1; i < ptpgc->nt; i++) {// check auto morph get the smallest
		wgperm.Import19(vv, ptpgc->t[i]);
		wgperm.MorphPuzzle(p, zem2);
		register int x = 0;
		for (; x < 81; x++)if (mywi.edp[x] != zem2[x])break;
		if (x < 81 && zem2[x] == '.') memcpy(mywi.edp, zem2, 81);
	}
	PuzzleInBitField(mywi.edp,mywi.n14);//// R_toR10(r)
	// build n25 
	memcpy(mywi.n25, R_toR10(mywi.rank),  10);
	mywi.n25[10] = ' ';
	memcpy(&mywi.n25[11], mywi.n14, 14);	mywi.Convertto19();
	return 0;
}
int Skname25to19(char* ze) {// convert r+b (25 or r;b) to 19" 
	mywi.Init();
	if (IsNotValidCallRB(ze)) return 1;
	//assumed valid to pack, no more check
	mywi.Convertto19();
	return 0;
}
int Skname25topuz(char* ze) {// 25 to 19 and ED puz
	mywi.Init();
	if (IsNotValidCallRB(ze)) return 1;
	mywi.Convertto19();
	if (GetEDpuz()) return 1; // should never be wrong
	return 0;
}
int Skname19to25(char* ze, int edpuz) {
	mywi.Init();
	if (strlen(ze) != 19)  return 1; 
	for (int i = 0; i < 5; i++) {
		register int ry = Get6Bits(i, ze);
		mywi.rank = (mywi.rank <<= 6) | ry;
	}
	register int rx = Get6Bits(5, ze);// 3 bits rank
	mywi.rank = (mywi.rank <<= 3) | (rx >> 3);
	rx &= 7;// residual bits for the 14 bytes field
	if (mywi.rank < 1) return 1;
	if (mywi.rank > 5472730538) return 1;
	for (int i = 6; i < 19; i++) {
		register int ry = Get6Bits(i, ze);
		rx = rx | ry & 070;
		mywi.n14[i - 6] = bit6[rx];
		rx = ry & 7;
	}
	mywi.n14[13] = bit6[rx];// last three bits
	memcpy(mywi.n19, ze, 18);
	// build n25 
	memcpy(mywi.n25, R_toR10(mywi.rank),10);
	mywi.n25[10] = ' ';
	memcpy(&mywi.n25[11], mywi.n14, 14);
	if (!edpuz) return 0;// ed puz not used
	// now convert rank + bitfield to ED puz
	return  GetEDpuz();
}


