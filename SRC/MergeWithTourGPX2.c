#include "LKH.h"
#include "gpx.h"

/*
 * The MergeWithTourGPX2 function attempts to find a short tour
 * by merging a given tour, T1, with another tour, T2.
 * T1 is given by the Suc pointers of its nodes.
 * T2 is given by the Next pointers of its nodes.
 *
 * The merging algorithm uses Generalized Partition Crossover 2,
 * GPX2, described in
 *
 *      R.Tinos, D. Whitley, and G. Ochoa (2017),
 *      A new generalized partition crossover for the traveling
 *      salesman problem: tunneling between local optima.
 */

GainType MergeWithTourGPX2()
{
    int *red, *blue, *offspring, i, NewDimension = 0;
    GainType Cost1 = 0, Cost2 = 0, NewCost;
    Node *N;

    n_cities = Dimension;
    red = (int *) malloc(n_cities * sizeof(int));
    blue = (int *) malloc(n_cities * sizeof(int));
    offspring = (int *) malloc((n_cities + 1) * sizeof(int));
    Map2Node = (Node **) malloc(n_cities * sizeof(Node *));
    GainType Penalty1 = 0, Penalty2 = 0, NewPenalty;

    if (Penalty) {
        CurrentPenalty = PLUS_INFINITY;
        Penalty1 = Penalty();
    }
    N = FirstNode;
    do {
        N->Suc->Pred = N->Next->Prev = N;
        N->SucSaved = N->Suc;
    } while ((N = N->Suc) != FirstNode);
    i = 0;
    do {
        Map2Node[i] = N;
        red[i] = N->Rank = i;
        i++;
        Cost1 += C(N, N->Suc) - N->Pi - N->Suc->Pi;
        if ((N->Suc != N->Prev && N->Suc != N->Next) ||
            (N->Pred != N->Prev && N->Pred != N->Next))
            NewDimension++;
    } while ((N = N->Suc) != FirstNode);
    if (NewDimension == 0) {
        free(red);
        free(blue);
        free(offspring);
        free(Map2Node);
        CurrentPenalty = Penalty1;
        return Cost1 / Precision;
    }
    if (Penalty) {
        N = FirstNode;
        do {
            N->OldSuc = N->Suc;
            (N->Suc = N->Next)->Pred = N;
        } while ((N = N->Suc) != FirstNode);
        CurrentPenalty = PLUS_INFINITY;
        Penalty2 = Penalty();
        do
            (N->Suc = N->OldSuc)->Pred = N;
        while ((N = N->Suc) != FirstNode);
    }
    i = 0;
    do {
        blue[i++] = N->Rank;
        Cost2 += C(N, N->Next) - N->Pi - N->Next->Pi;
    } while ((N = N->Next) != FirstNode);
    Cost1 /= Precision;
    Cost2 /= Precision;

    NewCost = gpx(red, blue, offspring);
    
    if (NewCost >= Cost1 || NewCost >= Cost2) {
        free(red);
        free(blue);
        free(offspring);
        CurrentPenalty = Penalty1;
        return Cost1;
    }
    offspring[n_cities] = offspring[0];
    for (i = 0; i < n_cities; i++) {
        N = Map2Node[offspring[i]];
        Node *NextN = Map2Node[offspring[i + 1]];
        N->Suc = NextN;
        NextN->Pred = N;
    }
    if (Penalty) {
        CurrentGain = 1;
        CurrentPenalty = Penalty1 <= Penalty2 ? Penalty1 : Penalty2;
        NewPenalty = Penalty();
        if (NewPenalty > Penalty1 || NewPenalty > Penalty2) {
            N = FirstNode;
            do
                N->SucSaved->Pred = N;
            while ((N = N->Suc = N->SucSaved) != FirstNode);
            CurrentPenalty = Penalty1;
            free(red);
            free(blue);
            free(offspring);
            free(Map2Node);
            return Cost1;
        }
        CurrentPenalty = NewPenalty;
    }
    Hash = 0;
    N = FirstNode;
    do
        Hash ^= Rand[N->Id] * Rand[N->Suc->Id];
    while ((N = N->Suc) != FirstNode);
    free(red);
    free(blue);
    free(offspring);
    free(Map2Node);
    if (TraceLevel >= 2)
        printff("GPX2: " GainFormat "\n",  NewCost);
    return NewCost;
}
