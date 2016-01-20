#ifndef __HW_TEST_H
#define __HW_TEST_H	

void HW_TEST_INIT(void);
void HW_TEST(void);


//INPUT
#define IN1     PDin(4)
#define IN2     PDin(3)
#define IN3     PDin(2)
#define IN4     PDin(1)
#define IN5     PDin(0)
#define IN6     PCin(12)
#define IN7     PCin(11)
#define IN8     PCin(10)
#define IN9     PAin(15)
#define IN10     PAin(10)
#define IN11     PAin(9)
#define IN12     PAin(8)
#define IN13     PCin(9)
#define IN14     PCin(8)
#define IN15     PCin(7)
#define IN16     PCin(6)
#define IN17     PDin(15)
#define IN18     PDin(14)
#define IN19     PDin(13)
#define IN20     PDin(12)
#define IN21     PDin(11)
#define IN22     PDin(10)
#define IN23     PDin(9)
#define IN24     PDin(8)
#define IN25     PBin(15)
#define IN26     PBin(14)
#define IN27     PBin(13)
#define IN28     PBin(12)

#define EX_IN1     PBin(11)
#define EX_IN2     PBin(10)
#define EX_IN3     PEin(15)
#define EX_IN4     PEin(14)
#define EX_IN5     PEin(13)
#define EX_IN6     PEin(12)
#define EX_IN7     PEin(11)
#define EX_IN8     PEin(10)
#define EX_IN9     PEin(9)
#define EX_IN10     PEin(8)
#define EX_IN11     PEin(7)
#define EX_IN12     PBin(2)
#define EX_IN13     PBin(1)
#define EX_IN14     PBin(0)
#define EX_IN15     PCin(5)
#define EX_IN16     PCin(4)
#define EX_IN17     PAin(4)

//OUTPUT
#define AUX2_CTR     PEout(4)
#define SF_RL2_CTR     PEout(2)




#endif