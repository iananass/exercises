#ifndef __MSP__H__
#define __MSH__H__
#include <iostream>

class MStackPrinter
{
    static int m_deep;
    const char* m_id;

public:

    MStackPrinter(const char* id)
    : m_id(id)
    {
        printIndent();
        std::cout << "#### " << m_id << std::endl;
        ++m_deep;
    }

    ~MStackPrinter()
    {
        --m_deep;
        printIndent();
        std::cout << "^^^^ " << m_id << std::endl;
    }

    static void printIndent()
    {
        for (int i = 0; i < m_deep; ++i)
            std::cout << "   ";
    }
};

#define STACK MStackPrinter msp(__PRETTY_FUNCTION__)
#define MSPLOG(log) do {MStackPrinter::printIndent(); std::cout << "@@@@ " << __PRETTY_FUNCTION__ << "   " << log << std::endl;} while(0)
#define PrintVal(x)  #x << " = '" << (x) << "'"
#endif
