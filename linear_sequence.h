#ifndef LINEAR_SEQUENCE_H
#define LINEAR_SEQUENCE_H

#include <stdlib.h>

/* Тип хранимых в контейнере значений */
typedef int LSQ_BaseTypeT;

/* Дескриптор контейнера */
typedef void* LSQ_HandleT;

/* Неинициализированное значение дескриптора контейнера */
#define LSQ_HandleInvalid NULL

/* Дескриптор итератора */
typedef void* LSQ_IteratorT;

/* Тип целочисленного индекса контейнера */
typedef int LSQ_IntegerIndexT;

extern LSQ_HandleT LSQ_CreateSequence(void);
extern void LSQ_DestroySequence(LSQ_HandleT handle);

extern LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle); //+


extern int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator);

extern int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator);

extern int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator);

extern LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator);

/* Следующие три функции создают итератор в памяти и возвращают его дескриптор */

extern LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index);

extern LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle);

extern LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle);


extern void LSQ_DestroyIterator(LSQ_IteratorT iterator);


extern void LSQ_AdvanceOneElement(LSQ_IteratorT iterator);

extern void LSQ_RewindOneElement(LSQ_IteratorT iterator);

extern void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift);

extern void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos);


extern void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element);

extern void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element);

extern void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement);


extern void LSQ_DeleteFrontElement(LSQ_HandleT handle);

extern void LSQ_DeleteRearElement(LSQ_HandleT handle);

extern void LSQ_DeleteGivenElement(LSQ_IteratorT iterator);

#endif
