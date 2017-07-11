#ifndef SETTINGS_H
#define SETTINGS_H


struct Settings
{
    int n = 5, m = 10, k = 5;
    float a = 0.0f, b = 1.0f, c = 0.0f, d = 6.3f;
    Settings(){}
    Settings(int n, int m, int k, float a, float b, float c, float d){
        this->n = n;
        this->m = m;
        this->k = k;
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
};

#endif // SETTINGS_H
