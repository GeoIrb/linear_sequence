#include "linear_sequence.h"

#define TST(T) ((TypeSequence*)(T))
#define TIT(T) ((TypeIterator*)(T))

typedef struct{
    LSQ_BaseTypeT *data_;
    LSQ_IntegerIndexT size_, capacity_;
} TypeSequence;

typedef struct{
    LSQ_IntegerIndexT index_;
    TypeSequence *sequence_;
} TypeIterator;

LSQ_HandleT LSQ_CreateSequence(void){
    TypeSequence *sequence = (TypeSequence*)malloc(sizeof (TypeSequence));

    if( sequence == NULL )
        return NULL;

    sequence->size_ = 0;
    sequence->capacity_ = 10;
    sequence->data_ = (LSQ_BaseTypeT*)calloc((size_t)sequence->capacity_, sizeof (LSQ_BaseTypeT));
    return (LSQ_HandleT)sequence;
}

void LSQ_DestroySequence(LSQ_HandleT handle){
    if(handle == LSQ_HandleInvalid)
        return;

    free(TST(handle)-> data_);
    free(handle);
}

LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle){
    if (handle == LSQ_HandleInvalid)
        return 0;
    return (TST(handle)-> size_);
}

int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator){
    return iterator != NULL && !LSQ_IsIteratorPastRear(iterator) && !LSQ_IsIteratorBeforeFirst(iterator);
}

int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator){
    return iterator != NULL && TIT(iterator)->index_ >= TIT(iterator)->sequence_->size_;
}

int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator){
    return iterator != NULL && TIT(iterator)->index_ < 0;
}

LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator){
    return !LSQ_IsIteratorDereferencable(iterator) ? NULL : TIT(iterator)->sequence_->data_ + TIT(iterator)->index_;
}

LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index){
    TypeIterator *iterator = (TypeIterator *)calloc(1, sizeof (TypeIterator));
    if(iterator == NULL || handle == LSQ_HandleInvalid)
        return NULL;

    iterator->index_ = index;
    iterator->sequence_ = TST(handle);

    return TIT(iterator);
}

LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle){
     return  handle == LSQ_HandleInvalid ? NULL : LSQ_GetElementByIndex(handle, 0);
}

LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle){
    LSQ_IntegerIndexT i = TST(handle)->size_ == 0 ? 0 : TST(handle)->size_ - 1;
    return  handle == LSQ_HandleInvalid ? NULL : LSQ_GetElementByIndex(handle, i);
}

void LSQ_DestroyIterator(LSQ_IteratorT iterator){
    if (iterator == NULL)
        return;

    LSQ_DestroySequence(TIT(iterator)->sequence_);
    free(iterator);
}

void LSQ_AdvanceOneElement(LSQ_IteratorT iterator){
    if (iterator == NULL)
        return;

    LSQ_IntegerIndexT newIndex = TIT(iterator)->index_ + 1;
    if(newIndex <= TIT(iterator)->sequence_->capacity_)
        TIT(iterator)->index_ = newIndex;
}

void LSQ_RewindOneElement(LSQ_IteratorT iterator){
    if (iterator == NULL)
        return;

    LSQ_IntegerIndexT newIndex = TIT(iterator)->index_ + 1;
    if(newIndex > 0)
        TIT(iterator)->index_ = newIndex;
}

void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift){
    if (iterator == NULL)
        return;

    LSQ_IntegerIndexT newIndex = TIT(iterator)->index_ + shift;
    if(newIndex > 0 && newIndex <= TIT(iterator)->sequence_->capacity_)
        TIT(iterator)->index_ = newIndex;
}

void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos){
    if (iterator == NULL)
        return;

    LSQ_IntegerIndexT newIndex = pos;
    if(newIndex > 0 && newIndex <= TIT(iterator)->sequence_->capacity_)
        TIT(iterator)->index_ = newIndex;
}

void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element){
    if( handle == LSQ_HandleInvalid )
        return;

    if( TST(handle)->size_ + 1 > TST(handle)->capacity_ ){
        LSQ_BaseTypeT *newData = (LSQ_BaseTypeT *)realloc(TST(handle)->data_, 2*TST(handle)->capacity_ * sizeof (LSQ_BaseTypeT));
        if(newData == NULL)
            return;

        TST(handle)->capacity_ = 2*TST(handle)->capacity_;
        TST(handle)->data_ = newData;
    }

    for(LSQ_IntegerIndexT i = TST(handle)->size_; i > 0; --i)
        TST(handle)->data_[i] = TST(handle)->data_[i - 1];

    ++TST(handle)->size_;

    TST(handle)->data_[0] = element;
}

void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element){
    if( handle == LSQ_HandleInvalid )
        return;

    if( TST(handle)->size_ + 1 > TST(handle)->capacity_ ){
        LSQ_BaseTypeT *newData = (LSQ_BaseTypeT *)realloc(TST(handle)->data_, 2*TST(handle)->capacity_ * sizeof (LSQ_BaseTypeT));
        if(newData == NULL)
            return;

        TST(handle)->capacity_ = 2*TST(handle)->capacity_;
        TST(handle)->data_ = newData;
    }

    TST(handle)->data_[TST(handle)->size_++] = element;
}

void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement){
    if( iterator == NULL )
        return;

    if(TIT(iterator)->sequence_->size_ + 1 > TIT(iterator)->sequence_->capacity_){
        LSQ_BaseTypeT *newData = (LSQ_BaseTypeT *)realloc(TIT(iterator)->sequence_->data_, 2*TIT(iterator)->sequence_->capacity_ * sizeof (LSQ_BaseTypeT));
        if(newData == NULL)
            return;

        TIT(iterator)->sequence_->capacity_ = 2*TIT(iterator)->sequence_->capacity_;
        TIT(iterator)->sequence_->data_ = newData;
    }

    for(LSQ_IntegerIndexT i = TIT(iterator)->sequence_->size_; i > TIT(iterator)->index_; --i)
        TIT(iterator)->sequence_->data_[i] = TIT(iterator)->sequence_->data_[i - 1];

    TIT(iterator)->sequence_->data_[TIT(iterator)->index_] = newElement;
}

void LSQ_DeleteFrontElement(LSQ_HandleT handle){
    if( handle == LSQ_HandleInvalid )
        return;

    TST(handle)->data_[0] = 0;

    --TST(handle)->size_;

    for(LSQ_IntegerIndexT i = 0; i < TST(handle)->size_; ++i)
        TST(handle)->data_[i] = TST(handle)->data_[i + 1];
}

void LSQ_DeleteRearElement(LSQ_HandleT handle){
    if( handle == LSQ_HandleInvalid )
        return;

    TST(handle)->data_[--TST(handle)->size_] = 0;
}


void LSQ_DeleteGivenElement(LSQ_IteratorT iterator){
    if( iterator == NULL )
        return;

    --TIT(iterator)->sequence_->size_;

    for(LSQ_IntegerIndexT i = TIT(iterator)->index_; i < TIT(iterator)->sequence_->size_; ++i)
        TIT(iterator)->sequence_->data_[i] = TIT(iterator)->sequence_->data_[i + 1];

    TIT(iterator)->sequence_->data_[TIT(iterator)->sequence_->size_] = 0;
}

