    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
   //_/  H8/3069F Include File   _/                                _/
  //_/               Ver. 1.0   _/                                _/
 //_/                          _/  2006/09/29   by Atsushi Ruike _/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


/******************************************************************/
/* 16bits timer                                                   */
/******************************************************************/
struct st_hex_itu{						/*                        */
	union{								/* .TSTR +                */
		unsigned char		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	      :5;	/*              |         */
			unsigned char	STR2  :1;	/*              |.STR2    */
			unsigned char	STR1  :1;	/*              |.STR1    */
			unsigned char	STR0  :1;	/*              |.STR0    */
		}BIT;							/*                        */
	}TSTR;								/* ---------------------- */
	union{								/* .TSNC +                */
		unsigned char		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	      :5;	/*              |         */
			unsigned char	SYNC2 :1;	/*              |.SYNC2   */
			unsigned char	SYNC1 :1;	/*              |.SYNC1   */
			unsigned char	SYNC0 :1;	/*              |.SYNC0   */
		}BIT;							/*                        */
	}TSNC;								/* ---------------------  */
	union{								/* .TMDR +                */
		unsigned char		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	      :1;	/*              |         */
			unsigned char	MDF   :1;	/*              |.MDF     */
			unsigned char	FDIR  :1;	/*              |.FDIR    */
			unsigned char	_     :2;	/*              |         */
			unsigned char	PWM2  :1;	/*              |.PWM2    */
			unsigned char	PWM1  :1;	/*              |.PWM1    */
			unsigned char	PWM0  :1;	/*              |.PWM0    */
		}BIT;							/*                        */
	}TMDR;								/* ---------------------- */
	union{								/* .TOLR +                */
		unsigned char		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	      :2;	/*              |         */
			unsigned char	TOB2  :1;	/*              |.TOB2    */
			unsigned char	TOB1  :1;	/*              |.TOB1    */
			unsigned char	TOB0  :1;	/*              |.TOB0    */
			unsigned char	TOA2  :1;	/*              |.TOA2    */
			unsigned char	TOA1  :1;	/*              |.TOA1    */
			unsigned char	TOA0  :1;	/*              |.TOA0    */
		}BIT;							/*                        */
	}TOLR;								/* ---------------------- */
	union{								/* .TISRA +               */
		unsigned char		BYTE;		/*        |.BYTE          */
		struct{							/*        |.BIT  +        */
			unsigned char	      :1;	/*               |        */
			unsigned char	IMIEA2:1;	/*               |.IMIEA2 */
			unsigned char	IMIEA1:1;	/*               |.IMIEA1 */
			unsigned char	IMIEA0:1;	/*               |.IMIEA0 */
			unsigned char	_     :1;	/*               |        */
			unsigned char	IMFA2 :1;	/*               |.IMFA2  */
			unsigned char	IMFA1 :1;	/*               |.IMFA1  */
			unsigned char	IMFA0 :1;	/*               |.IMFA0  */
		}BIT;							/*                        */
	}TISRA;								/* ---------------------- */
	union{								/* .TISRB +               */
		unsigned char		BYTE;		/*        |.BYTE          */
		struct{							/*        |.BIT  +        */
			unsigned char	      :1;	/*               |        */
			unsigned char	IMIEB2:1;	/*               |.IMIEB2 */
			unsigned char	IMIEB1:1;	/*               |.IMIEB1 */
			unsigned char	IMIEB0:1;	/*               |.IMIEB0 */
			unsigned char	_     :1;	/*               |        */
			unsigned char	IMFB2 :1;	/*               |.IMFB2  */
			unsigned char	IMFB1 :1;	/*               |.IMFB1  */
			unsigned char	IMFB0 :1;	/*               |.IMFB0  */
		}BIT;							/*                        */
	}TISRB;								/* ---------------------- */
	union{								/* .TISRC +               */
		unsigned char		BYTE;		/*        |.BYTE          */
		struct{							/*        |.BIT  +        */
			unsigned char	      :1;	/*               |        */
			unsigned char	OVIEB2:1;	/*               |.OVIEB2 */
			unsigned char	OVIEB1:1;	/*               |.OVIEB1 */
			unsigned char	OVIEB0:1;	/*               |.OVIEB0 */
			unsigned char	_     :1;	/*               |        */
			unsigned char	OVF2  :1;	/*               |.OVF2   */
			unsigned char	OVF1  :1;	/*               |.OVF1   */
			unsigned char	OVF0  :1;	/*               |.OVF0   */
		}BIT;							/*                        */
	}TISRC;								/*                        */
};										/*                        */
/******************************************************************/
/* 16bits timer channel 0-2                                       */
/******************************************************************/
struct st_hex_itu0{						/*                        */
	union{								/* .TCR +                 */
		unsigned char		BYTE;		/*      |.BYTE            */
		struct{							/*      |.BIT  +          */
			unsigned char	      :1;	/*             |          */
			unsigned char	CCLR  :2;	/*             |.CCLR     */
			unsigned char	CKEG  :2;	/*             |.CKEG     */
			unsigned char	TPSC  :3;	/*             |.TPSC     */
		}BIT;							/*                        */
	}TCR;								/* ---------------------- */
	union{								/* .TIOR +                */
		unsigned char		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	      :1;	/*              |         */
			unsigned char	IOB   :3;	/*              |.IOB     */
			unsigned char	_     :1;	/*              |         */
			unsigned char	IOA   :3;	/*              |.IOA     */
		}BIT;							/*                        */
	}TIOR;								/* ---------------------- */
	unsigned short			TCNT;		/* .TCNT                  */
	unsigned short			GRA;		/* .GRA                   */
	unsigned short			GRB;		/* .GRB                   */
};										/*                        */
/******************************************************************/
/* 8bits timer channel 0                                          */
/******************************************************************/
struct st_oct_itu0{						/*                        */
	union{								/* .TCR +                 */
		unsigned char 		BYTE;		/*      |.BYTE            */
		struct{							/*      |.BIT  +          */
			unsigned char	CMIEB :1;	/*             |.CMIEB    */
			unsigned char	CMIEA :1;	/*             |.CMIEA    */
			unsigned char	OVIE  :1;	/*             |.OVIE     */
			unsigned char	CCLR  :2;	/*             |.CCLR     */
			unsigned char	CKS   :3;	/*             |.CKS      */
		}BIT;							/*                        */
	}TCR;								/* ---------------------- */
	unsigned char			_;			/*                        */
	union{								/* .TCSR +                */
		unsigned char 		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	CMFB  :1;	/*              |.CMFB    */
			unsigned char	CMFA  :1;	/*              |.CMFA    */
			unsigned char	OVF   :1;	/*              |.OVF     */
			unsigned char	ADTE  :1;	/*              |.ADTE    */
			unsigned char	OIS32 :2;	/*              |.OIS32   */
			unsigned char	OS10  :2;	/*              |.OS10    */
		}BIT;							/*                        */
	}TCSR;								/* ---------------------- */
	unsigned char			__;			/*                        */
	unsigned char			TCORA;		/* .TCORA                 */
	unsigned char			___;		/*                        */
	unsigned char			TCORB;		/* .TCORB                 */
	unsigned char			____;		/*                        */
	unsigned char			TCNT;		/* .TCNT                  */
};										/*                        */
/******************************************************************/
/* 8bits timer channel 2                                          */
/******************************************************************/
struct st_oct_itu2{						/*                        */
	union{								/* .TCR +                 */
		unsigned char 		BYTE;		/*      |.BYTE            */
		struct{							/*      |.BIT  +          */
			unsigned char	CMIEB :1;	/*             |.CMIEB    */
			unsigned char	CMIEA :1;	/*             |.CMIEA    */
			unsigned char	OVIE  :1;	/*             |.OVIE     */
			unsigned char	CCLR  :2;	/*             |.CCLR     */
			unsigned char	CKS   :3;	/*             |.CKS      */
		}BIT;							/*                        */
	}TCR;								/* ---------------------- */
	unsigned char			_;			/*                        */
	union{								/* .TCSR +                */
		unsigned char 		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	CMFB  :1;	/*              |.CMFB    */
			unsigned char	CMFA  :1;	/*              |.CMFA    */
			unsigned char	OVF   :1;	/*              |         */
			unsigned char	      :1;	/*              |         */
			unsigned char	OIS32 :2;	/*              |.OIS32   */
			unsigned char	OS10  :2;	/*              |.OS10    */
		}BIT;							/*                        */
	}TCSR;								/* ---------------------- */
	unsigned char			__;			/*                        */
	unsigned char			TCORA;		/* .TCORA                 */
	unsigned char			___;		/*                        */
	unsigned char			TCORB;		/* .TCORC                 */
	unsigned char			____;		/*                        */
	unsigned char			TCNT;		/* .TCNT                  */
};										/*                        */
/******************************************************************/
/* 8bits timer channel 1&3                                        */
/******************************************************************/
struct st_oct_itu13{					/*                        */
	union{								/* .TCR +                 */
		unsigned char 		BYTE;		/*      |.BYTE            */
		struct{							/*      |.BIT  +          */
			unsigned char	CMIEB :1;	/*             |.CMIEB    */
			unsigned char	CMIEA :1;	/*             |.CMIEA    */
			unsigned char	OVIE  :1;	/*             |.OVIE     */
			unsigned char	CCLR  :2;	/*             |.CCLR     */
			unsigned char	CKS   :3;	/*             |.CKS      */
		}BIT;							/*                        */
	}TCR;								/* ---------------------- */
	unsigned char			_;			/*                        */
	union{								/* .TCSR +                */
		unsigned char 		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	CMFB  :1;	/*              |.CMFB    */
			unsigned char	CMFA  :1;	/*              |.CMFA    */
			unsigned char	OVF   :1;	/*              |.OVF     */
			unsigned char	      :1;	/*              |         */
			unsigned char	OIS32 :2;	/*              |.OIS32   */
			unsigned char	OS10  :2;	/*              |.OS10    */
		}BIT;							/*                        */
	}TCSR;								/* ---------------------  */
	unsigned char			__;			/*                        */
	unsigned char			TCORA;		/* .TCORA                 */
	unsigned char			___;		/*                        */
	unsigned char			TCORB;		/* .TCORB                 */
	unsigned char			____;		/*                        */
	unsigned char			TCNT;		/* .TCNT                  */
};										/*                        */
/******************************************************************/
/* WDT                                                            */
/******************************************************************/
struct st_wdt{							/*                        */
	union{								/* .RW +                  */
		union{							/*     |.WRITE +          */
			unsigned short	TCSR;		/*     |       |.TCSR     */
			unsigned short	TCNT;       /*     |       |.TCNT     */
		}WRITE;							/*     |                  */
		struct{							/*     |.READ  +          */
			unsigned char	TCSR;		/*             |.TCSR     */
			unsigned char	TCNT;		/*             |.TCNT     */
		}READ;							/*                        */
	}RW;								/* ---------------------- */
	union{								/* .RSTCSR +              */
		unsigned short		WRITE;		/*         |.WRITE        */
		struct{							/*         |.READ  +      */
			unsigned char	_;			/*                 |      */
			unsigned char	BYTE;		/*                 |.BYTE */
		}READ;							/*                        */
	}RSTCSR;							/*                        */
};										/*                        */
/******************************************************************/
/* Port 1.3.A.B                                                   */
/******************************************************************/
struct st_p13ab{						/*                        */
	unsigned char			DDR;		/* .DDR                   */
	unsigned char			_[0x11fcf];	/*                        */
	union{								/* .DR +                  */
		unsigned char		BYTE;		/*     |.BYTE             */
		struct{							/*     |.BIT  +           */
			unsigned char	B7    :1;	/*            |.B7        */
			unsigned char	B6    :1;	/*            |.B6        */
			unsigned char	B5    :1;	/*            |.B5        */
			unsigned char	B4    :1;	/*            |.B4        */
			unsigned char	B3    :1;	/*            |.B3        */
			unsigned char	B2    :1;	/*            |.B2        */
			unsigned char	B1    :1;	/*            |.B1        */
			unsigned char	B0    :1;	/*            |.B0        */
		}BIT;							/*                        */
	}DR;								/*                        */
};										/*                        */
/******************************************************************/
/* Port 2.4                                                       */
/******************************************************************/
struct st_p24{							/*                        */
	unsigned char			DDR;		/* .DDR                   */
	unsigned char			_[0x3a];	/*                        */
	union{								/* .PCR +                 */
		unsigned char		BYTE;		/*      |.BYTE            */
		struct{							/*      |.BIT  +          */
			unsigned char	B7    :1;	/*             |.B7       */
			unsigned char	B6    :1;	/*             |.B6       */
			unsigned char	B5    :1;	/*             |.B5       */
			unsigned char	B4    :1;	/*             |.B4       */
			unsigned char	B3    :1;	/*             |.B3       */
			unsigned char	B2    :1;	/*             |.B2       */
			unsigned char	B1    :1;	/*             |.B1       */
			unsigned char	B0    :1;	/*             |.B0       */
		}BIT;							/*                        */
	}PCR;								/* ---------------------- */
	unsigned char			__[0x11f94];/*                        */
	union{								/* .DR +                  */
		unsigned char		BYTE;		/*     |.BYTE             */
		struct{							/*     |.BIT  +           */
			unsigned char	B7    :1;	/*            |.B7        */
			unsigned char	B6    :1;	/*            |.B6        */
			unsigned char	B5    :1;	/*            |.B5        */
			unsigned char	B4    :1;	/*            |.B4        */
			unsigned char	B3    :1;	/*            |.B3        */
			unsigned char	B2    :1;	/*            |.B2        */
			unsigned char	B1    :1;	/*            |.B1        */
			unsigned char	B0    :1;	/*            |.B0        */
		}BIT;							/*                        */
	}DR;								/*                        */
};										/*                        */
/******************************************************************/
/* Port 5                                                         */
/******************************************************************/
struct st_p5{							/*                        */
	unsigned char			DDR;		/* .DDR                   */
	unsigned char			_[0x3a];	/*                        */
	union{								/* .PCR +                 */
		unsigned char		BYTE;		/*      |.BYTE            */
		struct{							/*      |.BIT  +          */
			unsigned char	      :4;	/*             |          */
			unsigned char	B3    :1;	/*             |.B3       */
			unsigned char	B2    :1;	/*             |.B2       */
			unsigned char	B1    :1;	/*             |.B1       */
			unsigned char	B0    :1;	/*             |.B0       */
		}BIT;							/*                        */
	}PCR;								/* ---------------------- */
	unsigned char			__[0x11f94];/*                        */
	union{								/* .DR +                  */
		unsigned char BYTE;				/*     |.BYTE             */
		struct{							/*     |.BIT  +           */
			unsigned char 	      :4;	/*            |           */
			unsigned char 	B3    :1;	/*            |.B3        */
			unsigned char 	B2    :1;	/*            |.B2        */
			unsigned char 	B1    :1;	/*            |.B1        */
			unsigned char 	B0    :1;	/*            |.B0        */
		}BIT;							/*                        */
	}DR;								/*                        */
};										/*                        */
/******************************************************************/
/* Port 6                                                         */
/******************************************************************/
struct st_p6{							/*                        */
	unsigned char			DDR;		/* .DDR                   */
	unsigned char			_[0x11fcf];	/*                        */
	union{								/* .DR +                  */
		unsigned char		BYTE;		/*     |.BYTE             */
		struct{							/*     |.BIT  +           */
			unsigned char	      :1;	/*            |           */
			unsigned char	B6    :1;	/*            |.B6        */
			unsigned char	B5    :1;	/*            |.B5        */
			unsigned char	B4    :1;	/*            |.B4        */
			unsigned char	B3    :1;	/*            |.B3        */
			unsigned char	B2    :1;	/*            |.B2        */
			unsigned char	B1    :1;	/*            |.B1        */
			unsigned char	B0    :1;	/*            |.B0        */
		}BIT;							/*                        */
	}DR;								/*                        */
};										/*                        */
/******************************************************************/
/* Port 7                                                         */
/******************************************************************/
struct st_p7{							/*                        */
	union{								/* .DR +                  */
		unsigned char		BYTE;		/*     |.BYTE             */
		struct{							/*     |.BIT  +           */
			unsigned char	B7    :1;	/*            |.B7        */
			unsigned char	B6    :1;	/*            |.B6        */
			unsigned char	B5    :1;	/*            |.B5        */
			unsigned char	B4    :1;	/*            |.B4        */
			unsigned char	B3    :1;	/*            |.B3        */
			unsigned char	B2    :1;	/*            |.B2        */
			unsigned char	B1    :1;	/*            |.B1        */
			unsigned char	B0    :1;	/*            |.B0        */
		}BIT;							/*                        */
	}DR;								/*                        */
};										/*                        */
/******************************************************************/
/* Port 8                                                         */
/******************************************************************/
struct st_p8{							/*                        */
	unsigned char			DDR;		/* .DDR                   */
	unsigned char			_[0x11fcf];	/*                        */
	union{								/* .DR +                  */
		unsigned char		BYTE;		/*     |.BYTE             */
		struct{							/*     |.BIT  +           */
			unsigned char	      :3;	/*            |           */
			unsigned char	B4    :1;	/*            |.B4        */
			unsigned char	B3    :1;	/*            |.B3        */
			unsigned char	B2    :1;	/*            |.B2        */
			unsigned char	B1    :1;	/*            |.B1        */
			unsigned char	B0    :1;	/*            |.B0        */
		}BIT;							/*                        */
	}DR;								/*                        */
};										/*                        */
/******************************************************************/
/* Port 9                                                         */
/******************************************************************/
struct st_p9{							/*                        */
	unsigned char			DDR;		/* .DDR                   */
	unsigned char			_[0x11fcf];	/*                        */
	union{								/* .DR +                  */
		unsigned char		BYTE;		/*     |.BYTE             */
		struct{							/*     |.BIT  +           */
			unsigned char	      :2;	/*            |           */
			unsigned char	B5    :1;	/*            |.B5        */
			unsigned char	B4    :1;	/*            |.B4        */
			unsigned char	B3    :1;	/*            |.B3        */
			unsigned char	B2    :1;	/*            |.B2        */
			unsigned char	B1    :1;	/*            |.B1        */
			unsigned char	B0    :1;	/*            |.B0        */
		}BIT;							/*                        */
	}DR;								/*                        */
};										/*                        */
/******************************************************************/
/* IRQ controller                                                 */
/******************************************************************/
struct st_irq{							/*                        */
	union{								/* .ISCR +                */
		unsigned char		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	      :2;	/*              |         */
			unsigned char	IRQ5SC:1;	/*              |.IRQ5SC  */
			unsigned char	IRQ4SC:1;	/*              |.IRQ4SC  */
			unsigned char	IRQ3SC:1;	/*              |.IRQ3SC  */
			unsigned char	IRQ2SC:1;	/*              |.IRQ2SC  */
			unsigned char	IRQ1SC:1;	/*              |.IRQ1SC  */
			unsigned char	IRQ0SC:1;	/*              |.IRQ0SC  */
		}BIT;							/*                        */
	}ISCR;								/* ---------------------- */
	union{								/* .IER +                 */
		unsigned char		BYTE;		/*      |.BYTE            */
		struct{							/*      |.BIT  +          */
			unsigned char	      :2;	/*             |          */
			unsigned char	IRQ5E :1;	/*             |.IRQ5E    */
			unsigned char	IRQ4E :1;	/*             |.IRQ4E    */
			unsigned char	IRQ3E :1;	/*             |.IRQ3E    */
			unsigned char	IRQ2E :1;	/*             |.IRQ2E    */
			unsigned char	IRQ1E :1;	/*             |.IRQ1E    */
			unsigned char	IRQ0E :1;	/*             |.IRQ0E    */
		}BIT;							/*                        */
	}IER;								/* ---------------------  */
	union{								/* .ISR +                 */
		unsigned char		BYTE;		/*      |.BYTE            */
		struct{							/*      |.BIT  +          */
			unsigned char	      :2;	/*             |          */
			unsigned char	IRQ5F :1;	/*             |.IRQ5F    */
			unsigned char	IRQ4F :1;	/*             |.IRQ4F    */
			unsigned char	IRQ3F :1;	/*             |.IRQ3F    */
			unsigned char	IRQ2F :1;	/*             |.IRQ2F    */
			unsigned char	IRQ1F :1;	/*             |.IRQ1F    */
			unsigned char	IRQ0F :1;	/*             |.IRQ0F    */
		}BIT;							/*                        */
	}ISR;								/* ---------------------- */
	unsigned char			_;			/*                        */
	union{								/* .IPRA +                */
		unsigned char		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	_IRQ0 :1;	/*              |.IPRA4   */
			unsigned char	_IRQ1 :1;	/*              |.IPRA4   */
			unsigned char	_IRQ23:1;	/*              |.IPRA4   */
			unsigned char	_IRQ45:1;	/*              |.IPRA4   */
			unsigned char	_WDT  :1;	/*              |.IPRA3   */
			unsigned char	_HEX_ITU0:1;/*              |.IPRA0   */
			unsigned char	_HEX_ITU1:1;/*              |.IPRA0   */
			unsigned char	_HEX_ITU2:1;/*              |.IPRA0   */
		}BIT;							/*                        */
	}IPRA;								/* ---------------------- */
	union{								/* .IPRB +                */
		unsigned char		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	_OCT_ITU01:1;/*             |.IPRB6   */
			unsigned char	_OCT_ITU23:1;/*             |.IPRB6   */
			unsigned char	_DMAC :1;	/*              |.IPRB5   */
			unsigned char	      :1;	/*              |         */
			unsigned char	_SCI0 :1;	/*              |.IPRB2   */
			unsigned char	_SCI1 :1;	/*              |.IPRB2   */
			unsigned char	_SCI2 :1;	/*              |.IPRB2   */
			unsigned char	      :1;	/*              |         */
		}BIT;							/*                        */
	}IPRB;								/*                        */
};										/*                        */
/******************************************************************/
/* A/D converter                                                  */
/******************************************************************/
struct st_ad{							/*                        */
	unsigned short			ADDRA;		/* .ADDRA                 */
	unsigned short			ADDRB;		/* .ADDRB                 */
	unsigned short			ADDRC;		/* .ADDRC                 */
	unsigned short			ADDRD;		/* .ADDRD                 */
	union{								/* .ADCSR +               */
		unsigned char		BYTE;		/*        |.BYTE          */
		struct{							/*        |.BIT  +        */
			unsigned char	ADF   :1;	/*               |.ADF    */
			unsigned char	ADIE  :1;	/*               |.ADIE   */
			unsigned char	ADST  :1;	/*               |.ADST   */
			unsigned char	SCAN  :1;	/*               |.SCAN   */
			unsigned char	CKS   :1;	/*               |.CKS    */
			unsigned char	CH    :3;	/*               |.CH     */
		}BIT;							/*                        */
	}ADCSR;								/* ---------------------- */
	union{								/* .ADCR +                */
		unsigned char		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	TRGE  :1;	/*              |.TRGE    */
			unsigned char	      :7;	/*              |         */
		}BIT;							/*                        */
	}ADCR;								/*                        */
};										/*                        */
/******************************************************************/
/* D/A converter                                                  */
/******************************************************************/
struct st_da{							/*                        */
	union{								/* .DASTCR +              */
		unsigned char		BYTE;		/*         |.BYTE         */
		struct{							/*         |.BIT  +       */
			unsigned char	      :7;	/*                |.DASTE */
			unsigned char	DASTE :1;	/*                        */
		}BIT;							/*                        */
	}DASTCR;							/* ---------------------- */
	unsigned char			_[0x11f81];	/*                        */
	unsigned char			DADR0;		/* .DADR0                 */
	unsigned char			DADR1;		/* .DADR1                 */
	union{								/* .DACR +                */
		unsigned char		BYTE;		/*       |.BYTE           */
		struct{							/*       |.BIT  +         */
			unsigned char	DAOE1 :1;	/*              |.DAOE1   */
			unsigned char	DAOE0 :1;	/*              |.DAOE0   */
			unsigned char	DAE   :1;	/*              |.DAE     */
			unsigned char	      :5;	/*              |         */
		}BIT;							/*                        */
	}DACR;								/*                        */
};										/*                        */
/******************************************************************/
union un_syscr {                                        // union SYSCR
               unsigned char BYTE;                      //  Byte Access
               struct {                                 //  Bit  Access
                      unsigned char SSBY :1;            //    SSBY
                      unsigned char STS  :3;            //    STS
                      unsigned char UE   :1;            //    UE
                      unsigned char NMIEG:1;            //    NMIEG
                      unsigned char SSOE :1;            //    SSOE
                      unsigned char RAME :1;            //    RAME
                      }      BIT;                       //
};                                                      //


#define HEX_ITU		(*(volatile struct 	st_hex_itu *)	0xFFFF60)
#define HEX_ITU0	(*(volatile struct 	st_hex_itu0 *)	0xFFFF68)
#define HEX_ITU1	(*(volatile struct 	st_hex_itu0 *)	0xFFFF70)
#define HEX_ITU2	(*(volatile struct 	st_hex_itu0 *)	0xFFFF78)
#define OCT_ITU0	(*(volatile struct 	st_oct_itu0 *)	0xFFFF80)
#define OCT_ITU1	(*(volatile struct 	st_oct_itu13 *)	0xFFFF81)
#define OCT_ITU2	(*(volatile struct 	st_oct_itu2 *)	0xFFFF90)
#define OCT_ITU3	(*(volatile struct 	st_oct_itu13 *)	0xFFFF91)
#define WDT			(*(volatile struct 	st_wdt *)		0xFFFF8C)
#define P1			(*(volatile struct 	st_p13ab *)		0xFEE000)
#define P2			(*(volatile struct 	st_p24 *)		0xFEE001)
#define P3			(*(volatile struct 	st_p13ab *)		0xFEE002)
#define P4			(*(volatile struct 	st_p24 *)		0xFEE003)
#define P5			(*(volatile struct 	st_p5 *)		0xFEE004)
#define P6			(*(volatile struct 	st_p6 *)		0xFEE005)
#define P7			(*(volatile struct 	st_p7 *)		0xFFFFD6)
#define P8			(*(volatile struct 	st_p8 *)		0xFEE007)
#define P9			(*(volatile struct 	st_p9 *)		0xFEE008)
#define PA			(*(volatile struct 	st_p13ab *)		0xFEE009)
#define PB			(*(volatile struct 	st_p13ab *)		0xFEE00A)
#define IRQ			(*(volatile struct 	st_irq *)		0xFEE014)
#define AD			(*(volatile struct 	st_ad *)		0xFFFFE0)
#define DA			(*(volatile struct 	st_da *)		0xFEE01A)

#define SYSCR   (*(volatile union  un_syscr *)0xFEE012) // SYSCR Address

#define load_segment(num) {int base;base = (*(volatile unsigned int *)(0xfffd10 + num * 4));asm("mov.l %0, er5" :: "r" (base));}
#define set_stack(stack) asm("mov.l %0, sp" :: "r" (stack))
