#include "LKH.h"

void SINTEF_WriteSolution(char *FileName)
{
    FILE *ResultFile;
    Node *N, *NextN;
    int Route, Forward;

    if (FileName == 0)
        return;
    if (TraceLevel >= 1)
        printff("Writing MTSP_SINTEF_RESULT_FILE: \"%s\" ... ", FileName);
    assert(ResultFile = fopen(FileName, "w"));
    fprintf(ResultFile, "Instance name : %s\n", Name);
    fprintf(ResultFile, "Authors       : Keld Helsgaun\n");
    fprintf(ResultFile, "Date          : %s\n", __DATE__);
    fprintf(ResultFile, "Reference     : %s\n", "LKH-3");
    fprintf(ResultFile, "Solution\n");
    N = Depot;
    Forward = N->Suc->Id != N->Id + DimensionSaved;
    Route = 0;
    do {
        Route++;
        fprintf(ResultFile, "Route %d : ", Route);
        do {
            if (N->Id <= Dim && N != Depot)
                fprintf(ResultFile, "%d%s ", N->Id - 1, /*
                                                           N->Delivery ? "D": N->Pickup ? "P" : */ "");
            NextN = Forward ? N->Suc : N->Pred;
            if (NextN->Id > DimensionSaved)
                NextN = Forward ? NextN->Suc : NextN->Pred;
            N = NextN;
        } while (N->DepotId == 0);
        fprintf(ResultFile, "\n");
    } while (N != Depot);
    fclose(ResultFile);
    if (TraceLevel >= 1)
        printff("done\n");
}
