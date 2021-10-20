#ifndef WYKRES_H
#define WYKRES_H

class wykres
{
    public:
    wykres();
    ~wykres();
    void operator() (const std::string & polecenie);
    FILE *wykrespipe;
};

wykres::wykres()
{
    wykrespipe = popen("gnuplot -persist","w");
    if(!wykrespipe)
    {
        std::cerr << "GNUPLOT not found!";
    }
}

wykres::~wykres()
{
    fprintf(wykrespipe,"exit\n");
    pclose(wykrespipe);
}

void wykres::operator() (const std::string & polecenie)
{
    fprintf(wykrespipe,"%s\n",polecenie.c_str());
    fflush(wykrespipe);
}


#endif