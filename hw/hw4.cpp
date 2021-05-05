boolean lock = false;

void acquiry(boolean *lock)
{
    while(!test_and_set(*lock))
        ; //do nothing
}

void release(boolean *lock)
{
    lock = false;
}