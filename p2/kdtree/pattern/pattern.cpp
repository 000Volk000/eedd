/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <pattern.hpp>

Pattern::Pattern()
{
    //
    _values = std::make_shared<std::valarray<float>>();
    _class_label = -1;
    //
    assert(dim() == 0);
    assert(class_label() == -1);
}

Pattern::Pattern(float *values, const size_t size, const int cl)
{
    assert(size > 0);
    //
    _values = std::make_shared<std::valarray<float>>(values, size);
    _class_label = cl;
    //
    assert(dim() == size);
    assert(class_label() == cl);
}

Pattern::~Pattern()
{
    //
    //
}

size_t Pattern::dim() const
{
    size_t d = 0;
    //
    d = _values->size();
    //
    return d;
}

int Pattern::class_label() const
{
    int cl = -1;
    //
    cl = _class_label;
    //
    return cl;
}

const std::valarray<float> &
Pattern::values() const
{
    //
    return *_values;
    //
}

void Pattern::set_class_label(const int new_label)
{
    //
    _class_label = new_label;
    //
    assert(class_label() == new_label);
}

std::valarray<float> &
Pattern::values()
{
    //
    return *_values;
    //
}

void Pattern::reset(float *values, const size_t size, const int cl)
{
    assert(size >= 0);
    //
    _values = std::make_shared<std::valarray<float>>(values, size);
    _class_label = cl;
    //
    assert(dim() == size);
    assert(class_label() == cl);
}

std::ostream &operator<<(std::ostream &output, const Pattern &p)
{
    //
    // Remember: format "[ class_label [ v0 v1 ... vn-1 ] ]"
    output << "[ " << p.class_label() << " [ ";
    auto aux = p.values();
    for (size_t i = 0; i < p.dim(); i++)
    {
        output << aux[i] << " ";
    }
    output << "] ]";
    //
    return output;
}

std::istream &operator>>(std::istream &in, Pattern &p) noexcept(false)
{
    //
    // Remember: input format is "[ class_label [ v_0 v_1 ... v_size-1 ] ]"
    std::string token;
    in >> token;
    if (token != "[")
    {
        throw std::runtime_error("wrong input format");
    }
    in >> token;
    int cl;
    std::istringstream iss(token);
    if (!(iss >> cl) || !(iss.eof()))
    {
        throw std::runtime_error("wrong input format");
    }
    in >> token;
    if (token != "[")
    {
        throw std::runtime_error("wrong input format");
    }

    std::vector<float> v;
    while ((in >> token) && (token != "]"))
    {
        float val;
        std::istringstream iss(token);
        if (!(iss >> val) || !(iss.eof()))
        {
            throw std::runtime_error("wrong input format");
        }
        v.push_back(val);
    }
    if (token != "]")
    {
        throw std::runtime_error("wrong input format");
    }
    if (!(in >> token) || (token != "]"))
    {
        throw std::runtime_error("wrong input format");
    }

    p.reset(v.data(), v.size(), cl);
    //
    return in;
}

float distance_L2(const Pattern &a, const Pattern &b)
{
    assert(a.dim() == b.dim());
    float dist = 0.0;
    //
    dist = sqrt((pow((a.values() - b.values()), 2)).sum());
    //
    assert(dist >= 0.0);
    return dist;
}

float distance_L1(const Pattern &a, const Pattern &b)
{
    assert(a.dim() == b.dim());
    float dist = 0.0;
    //
    dist = (abs(a.values() - b.values())).sum();
    //
    assert(dist >= 0.0);
    return dist;
}

std::istream &
load_dataset(std::istream &input,
             std::vector<Pattern> &dts) noexcept(false)
{
    //
    // Remember: input format is
    // "<size_t num_patterns> <size_t pattern_dimensions>
    // <p_0>
    // <p_1>
    // ...
    // <p_num_patterns-1>
    // "
    std::string token;
    input >> token;
    std::istringstream iss(token);
    size_t n;
    if (!(iss >> n) || !(iss.eof()))
    {
        throw std::runtime_error("wrong input format");
    }
    input >> token;
    iss.clear();
    iss.str(token);
    size_t dim;
    if (!(iss >> dim) || !(iss.eof()))
    {
        throw std::runtime_error("wrong input format");
    }
    dts.resize(n);

    for (size_t i = 0; i < n; i++)
    {
        input >> dts[i];
        if (dts[i].dim() != dim)
        {
            throw std::runtime_error("wrong input format");
        }
    }
    //
    return input;
}
