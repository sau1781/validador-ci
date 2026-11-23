#include "minitest.h"
#include "credencial.h"

static void test_formato_acepta_ocho_digitos(void)
{
    MT_ASSERT_EQ(cred_formato_valido("12345678"), 1);
    MT_ASSERT_EQ(cred_formato_valido("1234"), 0);
    MT_ASSERT_EQ(cred_formato_valido("1234abcd"), 0);
}

static void test_checksum_valido(void)
{
    MT_ASSERT_EQ(cred_checksum("12345678"), 8);
    MT_ASSERT_EQ(cred_checksum("invalido"), -1);
}

static void test_autorizar_casos(void)
{
    const char *lista[] = {"12345678", "00000000"};
    MT_ASSERT_EQ(cred_autorizar("12345678", lista, 2), CRED_OK);
    MT_ASSERT_EQ(cred_autorizar("12345679", lista, 2), CRED_ERR_CHECKSUM);
    MT_ASSERT_EQ(cred_autorizar("11111117", lista, 2), CRED_ERR_NO_AUTORIZADA);
    MT_ASSERT_EQ(cred_autorizar("abc", lista, 2), CRED_ERR_FORMATO);
}

int main(void)
{
    printf("Pruebas del validador de credenciales\n");
    printf("-------------------------------------\n");

    MT_PRUEBA(test_formato_acepta_ocho_digitos);
    MT_PRUEBA(test_checksum_valido);
    MT_PRUEBA(test_autorizar_casos);

    return mt_informe("build/reports/credencial.xml", "credencial");
}
