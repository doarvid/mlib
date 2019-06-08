#include "m-serial-json.h"
#include "m-tuple.h"
#include "m-array.h"

// Serial json is not supported for standard types if not C11
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L  

TUPLE_DEF2(person,
           (surname, string_t),
           (age, int),
           (present, bool)
           )
#define M_OPL_person_t() TUPLE_OPLIST(person, M_DEFAULT_OPLIST, STRING_OPLIST, M_DEFAULT_OPLIST )

ARRAY_DEF(base, person_t)
#define M_OPL_base_t() ARRAY_OPLIST(base, M_OPL_person_t())

static void read(base_t base, const char filename[])
{
  m_serial_read_t  in;
  m_serial_return_code_t ret;

  FILE *f = fopen(filename, "rt");
  if (!f) {
    fprintf(stderr, "ERROR: Cannot open file '%s'.\n", filename);
    exit(2);
  }
  m_serial_json_read_init(in, f);
  ret = base_in_serial(base, in);
  if (ret != M_SERIAL_OK_DONE) {
    fprintf(stderr, "ERROR: Cannot read JSON data from file '%s'.\n", filename);
    exit(2);
  }
  m_serial_json_read_clear(in);
  fclose(f);
}

int main(void)
{
  M_LET(base, base_t) {
    read(base, "ex-json01.json");
    printf ("List of presents:\n");
    for M_EACH(el, base, base_t) {
        if ((*el)->present) {
          printf("%s\n", string_get_cstr((*el)->surname));
        }
      }
  }
  exit(0);    
}

#else
int main(void)
{
  exit(0);    
}
#endif