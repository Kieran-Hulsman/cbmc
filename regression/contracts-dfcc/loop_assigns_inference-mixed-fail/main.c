#define N 10

int g;

void incr(int *p)
{
  (*p)++;
}

void set_g(void)
{
  g = 2;
}

int main()
{
  int x = 0;
  g = 0;
  int y = 0;

  for(int i = 0; i < N; i++)
    // clang-format off
    __CPROVER_assigns(i, x)
    __CPROVER_loop_invariant(0 <= i && i <= N && x == i)
    // clang-format on
    {
      incr(&x);
    }
  __CPROVER_assert(x == N, "x counts the iterations");

  for(int j = 0; j < N; j++)
    // clang-format off
    __CPROVER_loop_invariant(0 <= j && j <= N)
    // clang-format on
    {
      if(j == 5)
      {
        set_g();
        incr(&y);
      }
    }
  __CPROVER_assert(g == 0, "g written as a global");            // must fail
  __CPROVER_assert(y == 0, "y written through a parameter");    // must fail
  __CPROVER_assert(x == N, "x not written by the second loop"); // must pass
  return 0;
}
