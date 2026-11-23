#include "credencial.h"
#include <stddef.h>
#include <string.h>
#include <ctype.h>

int cred_formato_valido(const char *uid)
{
    if (uid == NULL || strlen(uid) != CRED_LONGITUD) {
        return 0;
    }
    for (size_t i = 0; i < CRED_LONGITUD; ++i) {
        if (!isdigit((unsigned char)uid[i])) {
            return 0;
        }
    }
    return 1
}

int cred_checksum(const char *uid)
{
    if (!cred_formato_valido(uid)) {
        return -1;
    }
    int suma = 0;
    for (size_t i = 0; i < CRED_LONGITUD - 1; ++i) {
        suma += (uid[i] - '0');
    }
    return suma % 10;
}

cred_resultado_t cred_autorizar(const char *uid,
                                const char *permitidas[],
                                size_t n)
{
    if (!cred_formato_valido(uid)) {
        return CRED_ERR_FORMATO;
    }
    int esperado = cred_checksum(uid);
    int real = uid[CRED_LONGITUD - 1] - '0';
    if (esperado != real) {
        return CRED_ERR_CHECKSUM;
    }
    if (permitidas != NULL) {
        for (size_t i = 0; i < n; ++i) {
            if (permitidas[i] != NULL && strcmp(uid, permitidas[i]) == 0) {
                return CRED_OK;
            }
        }
    }
    return CRED_ERR_NO_AUTORIZADA;
}

const char *cred_nombre_resultado(cred_resultado_t r)
{
    switch (r) {
    case CRED_OK:                 return "OK";
    case CRED_ERR_FORMATO:        return "ERR_FORMATO";
    case CRED_ERR_CHECKSUM:       return "ERR_CHECKSUM";
    case CRED_ERR_NO_AUTORIZADA:  return "ERR_NO_AUTORIZADA";
    default:                      return "DESCONOCIDO";
    }
}
