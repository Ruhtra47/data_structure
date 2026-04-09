#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

typedef struct Professor
{
    char name[32];
    float reproved_ratio;
    Vector *subjects;
} Professor;

typedef struct Subject
{
    char name[32];
    int n_students;
    int n_approved;
    float reproved_ratio;
} Subject;

Professor *read_professor();
Subject *read_subject();

int main()
{
    Vector *professors = vector_construct();

    int n;
    scanf("%d", &n);

    float mean_ratio = 0.0;
    for (int i = 0; i < n; i++)
    {
        vector_push_back(professors, read_professor());

        Professor *p = (Professor *)vector_get(professors, i);
        mean_ratio += p->reproved_ratio;
    }

    mean_ratio /= (float)n;

    for (int i = 0; i < n; i++)
    {
        Professor *p = (Professor *)vector_get(professors, i);

        if (p->reproved_ratio > mean_ratio)
        {
            printf("%s\n", p->name);
        }
    }

    // Liberar a memoria

    for (int i = 0; i < n; i++)
    {
        Professor *p = (Professor *)vector_get(professors, i);

        for (int j = 0; j < vector_size(p->subjects); j++)
        {
            Subject *s = (Subject *)vector_get(p->subjects, j);
            free(s);
        }
        vector_destroy(p->subjects);
        free(p);
    }
    vector_destroy(professors);
}

Professor *read_professor()
{
    Professor *p = (Professor *)malloc(sizeof(Professor));
    scanf("%s", p->name);

    int m;
    scanf("%d", &m);

    p->subjects = vector_construct();

    p->reproved_ratio = 0;
    for (int i = 0; i < m; i++)
    {
        vector_push_back(p->subjects, read_subject());

        Subject *s = (Subject *)vector_get(p->subjects, i);
        p->reproved_ratio += s->reproved_ratio;
    }

    p->reproved_ratio /= (float)m;

    return p;
}

Subject *read_subject()
{
    Subject *s = (Subject *)malloc(sizeof(Subject));
    scanf("%s", s->name);
    scanf("%d", &s->n_students);
    scanf("%d", &s->n_approved);

    s->reproved_ratio = (float)s->n_approved / (float)s->n_students;
    s->reproved_ratio = 1 - s->reproved_ratio;

    return s;
}