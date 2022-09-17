/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
* All Rights Reserved
*
*************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* Comments:
*
*   This file contains interrupt controller specific initialization functions.
*
*END************************************************************************/

#include "derivative.h"
#include "hidef.h" /* for EnableInterrupts macro */
#include "Int_Ctl_cfv2.h"


 uint_32 get_sr (void);
 void set_sr(uint_32 x);

/***************************************************************************
 * Local Functions Prototypes 
 ***************************************************************************/


/***************************************************************************
 * Local Functions 
 ***************************************************************************/
 
 
__declspec(register_abi) static asm uint_32 get_sr (void)
{

   move.w   sr,d0
   rts
   
} 

__declspec(register_abi) static asm void set_sr(uint_32 x)
  
{ /* Body */


   move.w   d0,sr
   rts
   
   
} /* Endbody */



/***************************************************************************
 * Global Functions 
 ***************************************************************************/
 
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_platform_init
* Returned Value   : 0 for success
* Comments         :
*    This function performs BSP-specific related to the MCF51JM platform
*
*END*----------------------------------------------------------------------*/
void Int_Ctl_int_init(uint_8 int_ctl_no, uint_8 source_no, uint_8 level,uint_8 priority, boolean unmask)
{
uint_32 mask_bit;
vuint32* pMaskReg;
uint_8 lp;
vuint8* pICRn;
uint_32 temp_sr;

if(int_ctl_no > 1)
{
 return;
}

temp_sr = get_sr();
set_sr(temp_sr | 0x0700);

lp = (uint_8)((level<<3)|(priority));

if(int_ctl_no == 0)
{	
   /* INTC 0 */
   if(source_no <= 31)	
   {
    	pMaskReg = &MCF_INTC0_IMRL;
	    mask_bit = (uint_32)1<<source_no;
   }
   else
   {
    	pMaskReg = &MCF_INTC0_IMRH;
	    mask_bit = (uint_32)1<<(source_no - 32);
   }
	
   if(unmask)
   {
   	    MCF_INTC0_IMRL &= (~1);
    	*pMaskReg &= (~mask_bit);	   
   }
   else
   {
    	*pMaskReg |= mask_bit;
   }

   pICRn = &MCF_INTC0_ICR01 + source_no - 1;
}
#ifndef __MCF52221_H__
else
{	
   /* INTC 1 */
   if(source_no <= 31)	
   {
    	pMaskReg = &MCF_INTC1_IMRL;
	    mask_bit = (uint_32)1<<source_no;
   }
   else
   {
    	pMaskReg = &MCF_INTC1_IMRH;
	    mask_bit = (uint_32)1<<(source_no - 32);
   }
	
   if(unmask)
   {
   	    MCF_INTC1_IMRL &= (~1);
    	*pMaskReg &= (~mask_bit);
   }
   else
   {
    	*pMaskReg |= mask_bit;
   }

   pICRn = &MCF_INTC1_ICR01 + source_no - 1;
}
#endif

  *pICRn = lp;

  set_sr(temp_sr);
	
}
