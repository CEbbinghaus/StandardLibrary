#pragma once;
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <new>

using uint = unsigned int;

class String {
    uint length;
    char* data;

    static int findMin(int x, int y, int z) {
        if (x <= y && x <= z)
            return x;
        else if (y <= x && y <= z)
            return y;
        else
            return z;
    }

    void allocateData(){
        data = (char*)malloc(length + 1);
        if (data == nullptr) throw std::bad_alloc();
    }

    static char* allocateData(uint length){
        char* tmp = (char*)malloc(length + 1);
        if (tmp == nullptr) throw  std::bad_alloc();
        return tmp;
    }

    void copyData(const char* source){
        memcpy((void*)data, source, length);
        data[length] = '\0';
    }

    static char* copyData(char* dest, char* src, uint length){
        memcpy((void*)dest, src, length);
        dest[length] = '\0';
        return dest;
    }

    void destroyData() {
        if (data != nullptr)
            free((void*)data);
        data = nullptr;
    }

   public:
    static String format(const char* base, ...) {
        va_list argptr;
        va_start(argptr, base);
        size_t needed = vsnprintf(NULL, 0, base, argptr) + 1;
        char* buffer = (char*)malloc(needed);
        vsprintf(buffer, base, argptr);
        va_end(argptr);
        String result = String(buffer);
        free(buffer);
        return result;
    }

    static int LevinSteinDistance(const String& a, const String& b) {
        // Declaring a 2D array on the heap dynamically:
        int len_a = strlen(a.data) + 1;
        int len_b = strlen(b.data) + 1;

        int** d = new int*[len_a];
        for (int i = 0; i < len_a; i++)
            d[i] = new int[len_b];

        // Initialising first column:
        for (int i = 0; i < len_a; i++)
            d[i][0] = i;

        // Initialising first row:
        for (int j = 0; j < len_b; j++)
            d[0][j] = j;

        // Applying the algorithm:
        int insertion, deletion, replacement;

        for (int i = 1; i < len_a; i++) {
            for (int j = 1; j < len_b; j++) {
                if (a.data[i - 1] == b.data[j - 1]) {
                    d[i][j] = d[i - 1][j - 1];
                } else {
                    // Choosing the best option:
                    insertion = d[i][j - 1];
                    deletion = d[i - 1][j];
                    replacement = d[i - 1][j - 1];

                    d[i][j] = 1 + findMin(insertion, deletion, replacement);
                }
            }
        }

        int answer = d[len_a][len_b];

        for (int i = 0; i < len_a + 1; i++) {
            delete[] d[i];
        }
        delete[] d;

        return answer;
    }

    String(){
        length = 1;
        allocateData();
        data[0] = '\0';
    }

    String(const char* inData){

        length = strlen(inData);
        
        allocateData();
        copyData(inData);
    }

    String(const String& source){
        length = source.length;
        allocateData();
        copyData(source.data);
    }

    String(String&& source) noexcept{
        length = source.length;
        data = source.data;
        source.data = nullptr;
    }

    ~String() {
        //Delete Data if it Exists
        destroyData();
    }

    String& operator=(const String& other) {
        destroyData();

        //Assign and Allocate local Memory
        length = other.length;

        allocateData();
        copyData(other.data);

        return *this;
    }

    String& operator=(String&& other) noexcept {
        destroyData();

        //Assign and Allocate local Memory
        length = other.length;
        data = other.data;
        other.data = nullptr;

        return *this;
    }

    String& operator=(const char* inData) {
        destroyData();

        length = strlen(inData);
        
        allocateData();
        copyData(inData);
        
        return *this;
    }

    bool operator ==(const String& other) {
        return strcmp(this->data, other.data) == 0;
    }

    bool operator !=(const String& other) {
        return strcmp(this->data, other.data) != 0;
    }

    String operator +(const String& other) {
        //Allocates the Combined Length of Both strings + 1 for the Null Terminator
        uint totalLength = length + other.length;
        char* strData = allocateData(totalLength);

        //Copies the Data into the String and Sets the last character to Null
        memcpy(strData, data, length);
        memcpy(strData + length, other.data, other.length);
        strData[totalLength] = '\0';

        String result = String(strData);
        free(strData);
        return result;
    }

    String operator+(const char* other) {
        //Allocates the Combined Length of Both strings + 1 for the Null Terminator
        uint otherLength = strlen(other);
        uint totalLength = length + otherLength;
        char* strData = allocateData(totalLength);

        //Copies the Data into the String and Sets the last character to Null
        memcpy(strData, data, length);
        memcpy(strData + length, other, otherLength);
        strData[totalLength] = '\0';

        String result = String(strData);
        free(strData);
        return result;
    }

    String& operator+=(const String& other) {
        //Allocates the Combined Length of Both strings + 1 for the Null Terminator
        uint totalLength = length + other.length;
        char* strData = allocateData(totalLength);

        //Copies the Data into the String and Sets the last character to Null
        memcpy(strData, data, length);
        memcpy(strData + length, other.data, other.length);
        strData[totalLength] = '\0';

        //Update Values
        destroyData();
        data = strData;
        length = totalLength;

        return *this;
    }

    String& operator+=(const char* other) {
        //Allocates the Combined Length of Both strings + 1 for the Null Terminator
        uint otherLength = strlen(other);
        uint totalLength = length + otherLength;
        char* strData = allocateData(totalLength);

        //Copies the Data into the String and Sets the last character to Null
        memcpy(strData, data, length);
        memcpy(strData + length, other, otherLength);
        strData[totalLength] = '\0';

        //Update Values
        destroyData();
        data = strData;
        length = totalLength;

        return *this;
    }

    const char* CString() const{
        return data;
    }

    operator const char*() const{
        return data;
    }
};