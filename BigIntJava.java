// Initialisation
BigInteger A, B, C;
A = BigInteger.valueOf(10);
B = new BigInteger("10");

// cer = 2 or 3
boolean isprime = A.isProbablePrime(cer);		
// C is the next prime after A
C = A.nextProbablePrime();						

// BigDecimal (init same as BigInt)
// C = A + B. MathContext is optional. 
// Same for subtract and divide
C = A.add(B, new MathContext(6));      			
// C = A / B. Scale is no. of digits after decimal
C = A.divide(B, scale, new MathContext(6));   	
C = A.divide(B, scale, RoundingMode.CEILING);
// C = int(A / B)
C = A.divideToIntegralValue(B);					
C = A.setScale(6);								
// Precision of 4 places(including before decimal)	
C = A.round(new MathContext(4));				
