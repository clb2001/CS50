#include <cs50.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[i] = rank;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i; i < candidate_count; i++)
    {
        for (int j; j < candidate_count; j++)
        {
            if (ranks[i] < ranks[j])
            {
                // Keep-in-mind, prefrences is a global int array, which means all it's elements are already initialised to zeros
                preferences[i][j] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 1; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (preference[i][j] > preference[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
            else if (preference[i][j] < preference[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
            else
            {
                continue;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // don't know how to do it.
    int a, b;
    int i, j;
    pair temp;
    for (i = 0; i < pair_count - 1; i++)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[i].loser][pairs[i].winner])
        {
            a = preferences[pairs[i].winner][pairs[i].loser];
        }
        else if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i].loser][pairs[i].winner])
        {
            a = preferences[pairs[i].loser][pairs[i].winner];
        }
        for (j = 0; j < pair_count - 1 - i; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[j].loser][pairs[j].winner])
            {
                b = preferences[pairs[j].winner][pairs[j].loser];
                if (a < b)
                {
                    temp = pairs[j];
                    pairs[j] = pairs[j + 1];
                    pairs[j + 1] = temp;
                }
            }
            else if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j].loser][pairs[j].winner])
            {
                b = preferences[pairs[j].loser][pairs[j].winner];
                if (a < b)
                {
                    temp = pairs[j];
                    pairs[j] = pairs[j + 1];
                    pairs[j + 1] = temp;
                }
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count - 1; i++)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[i].loser][pairs[i].winner])
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i].loser][pairs[i].winner])
        {
            locked[pairs[i].loser][pairs[i].winner] = true;
        }
    }
    
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}