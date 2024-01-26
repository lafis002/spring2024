#include<CDC8600.hh>
#include<assert.h>

namespace CDC8600
{
   namespace instructions
   {   
        bool jmpz // Jump to P + K if (Xj) equal to 0 				(p94)
	(
	    uint8_t Xj
	)
	{
	    assert(Xj < 16);
	    if (0 == PROC.X(Xj).u()) return true;
	    else return false;
	}

	bool jmpp  // Jump to P + K if (Xj) positive 				(p98)
	(
	    uint8_t Xj
	)
	{
	    assert(Xj < 16);
	    if (0 < PROC.X(Xj).i()) return true;
	    else return false;
	}
	
        void xkj
	(
	    uint8_t Xj, 
	    uint8_t k
	)
	{
	    assert(Xj < 16);
	    assert(k < 16);
	    PROC.X(Xj).u() = k;
	}

        void rdjki // Xi = MEM[Xj + Xk]
	(
	    uint8_t Xi, 
	    uint8_t Xj, 
	    uint8_t Xk
	)
	{
	    assert(Xi < 16);
	    assert(Xj < 16);
		assert(Xk < 16);
		PROC.X(Xi).i() = MEM[PROC.X(Xj).u() + PROC.X(Xk).i()].i();

		if (PROC.X(Xj).u() + PROC.X(Xk).i() < PROC.FL().u()*256 + PROC.RA().u() && PROC.X(Xj).u() + PROC.X(Xk).i() > PROC.RA().u() )
	    {
		// Good
		uint32_t addr = PROC.X(Xi).i() = MEM[PROC.X(Xj).u() + PROC.X(Xk).i()].i();;	// Architected address
		assert(addr < params::MEM::N);		// Check against hardware limit
		PROC.X(Xj) = MEM[addr];
	    }
	    else
	    {
		// Bad
		PROC.cond()(2) = true;
		PROC._XA = PROC.XA().u();
	    }
	}

        void sdjki
	(
	    uint8_t Xi, 
	    uint8_t Xj, 
	    uint8_t Xk
	)
	{
	    assert(Xi < 16);
	    assert(Xj < 16);
		assert(Xk < 16);
		MEM[PROC.X(Xj).u() + PROC.X(Xk).i()].i() = PROC.X(Xi).i();
	
	}

        void isjki  
	(
	    uint8_t Xi, 
	    uint8_t Xj, 
	    uint8_t Xk
	)
	{
	    assert(Xi < 16);
	    assert(Xj < 16);
		assert(Xk < 16);
		PROC.X(Xi).i() = PROC.X(Xj).i() + PROC.X(Xk).i();
	}
	
        void idjkj //Xj = Xj - k
	(
	    uint8_t Xj, 
	    uint8_t k
	)
	{
	    assert(Xj < 16);
	    assert(k < 16);
		PROC.X(Xj).i() = PROC.X(Xj).i() - k;
	}

	void idzkj // Xj = -Xk
	(
	   uint8_t Xj,
	   uint8_t Xk
	)
	{
	    assert(Xj < 16);
	    assert(Xk < 16);
	    PROC.X(Xj).i() = (-1) * PROC.X(Xk).i();
	}

	void isjkj  //Xj = Xj + k
	(
	    uint8_t Xj,
	    uint8_t k
	)
	{
	    assert(Xj < 16);
	    assert(k < 16);
		PROC.X(Xj).i() = PROC.X(Xj).i() + k;
	}

	void ipjkj // Xj = Xj * Xk
	(
	    uint8_t Xj,
	    uint8_t Xk
	)
	{
	    assert(Xj < 16);
	    assert(Xk < 16);
	    PROC.X(Xj).i() = PROC.X(Xj).i() * PROC.X(Xk).i();
	}

	void rdKj
	(
	    uint8_t Xj,
	    uint32_t K
	)
	{
	    assert(Xj < 16);
	    assert(K < 1024*1024);

	    if (K < PROC.FL().u()*256)
	    {
		// Good
		uint32_t addr = PROC.RA().u()*256 + K;	// Architected address
		assert(addr < params::MEM::N);		// Check against hardware limit
		PROC.X(Xj) = MEM[addr];
	    }
	    else
	    {
		// Bad
		PROC.cond()(2) = true;
		PROC._XA = PROC.XA().u();
	    }
	}

   } // namespace instructions
} // namespace CDC8600
