#define N 10

int g;

void incr(int *p)
{
  (*p)++;
}

void add_two(void)
{
  g += 2;
}

int main()
{
  int x = 0;
  g = 0;

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
    __CPROVER_loop_invariant(0 <= j && j <= N && g == 2 * j)
    // clang-format on
    {
      add_two();
    }
  __CPROVER_assert(g == 2 * N, "g counts twice the iterations");
  __CPROVER_assert(x == N, "x not written by the second loop");
  return 0;
}
