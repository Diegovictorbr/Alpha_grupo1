//---------------------------------------------------------------------------
#ifndef AlphaH
#define AlphaH
//---------------------------------------------------------------------------
void   N_alpha(unsigned char* xy, unsigned char delta_linha);
void   L_alpha(unsigned char* e,unsigned char* s);
void   L_alpha2(unsigned char* e,unsigned char* s);
void  ExpandeChave(unsigned char* KEY,unsigned char XK[][16],int Nr);
void   N_alphat(unsigned char* xy, unsigned char delta_linha);//byte xy e o que sera substituido por zw

#endif
 