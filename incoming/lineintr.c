/*==========================================================================
	lineintr.c: Liniear Interporation
	$Author$
	$Revision$
	$Date$
==========================================================================*/

/*****  Includes **********************************************************/

/*****  Definitions  ******************************************************/

/*****  Enums *************************************************************/

/*****  Typedefs  *********************************************************/

/*****  External Variables  ***********************************************/

/*****  Global Variables  *************************************************/

/*****  Static Variables  *************************************************/

/*****  External Function's Prototypes  ***********************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*****  Static Function's Prototypes  *************************************/

/**************************************************************************/
/*-----------------------------------------------------------------------------
	prog  :	ikeda
	func  :	---
	entry :
	return:
	remks :	---
-----------------------------------------------------------------------------*/
double lineintr(double cx, double ax, double ay, double bx, double by)
{
	double coef;

	coef = (cx - ax)/(bx - ax);

	return coef*by + (1.0 - coef)*ay;
}

/*==========================================================================
	$Log$
==========================================================================*/