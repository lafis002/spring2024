class fmuljki : public Fijk {

    public:
	fmuljki(u08 i, u08 j, u08 k) : Fijk(0xA, i, j, k) {}

    bool execute()
    {
        PROC.X(_i).f() = PROC.X(_j).f() * PROC.X(_k).f();
    }

    string mnemonic() const
    {
        return "fmuljki";
    }
};