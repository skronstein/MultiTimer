bool ptrIsValid(void *pointer) {
    if((long)pointer != 0)
        return true;
    else
        return false;
}