#include <table-mediator.hpp>

namespace GameTrainer::mylib::xml {
    TableMediator::TableMediator(std::ifstream *file)
    {
        this->setters.push_back(new DescriptionSetter(file));
        this->setters.push_back(new VariableTypeSetter(file));
        this->setters.push_back(new AddressSetter(file));
        this->setters.push_back(new OffsetsSetter(file));
    }

    TableMediator::~TableMediator()
    {
        for (TableSetter* setter : this->setters)
        {
            delete setter;
        }

        this->setters.clear();
    }

    void TableMediator::setProps(const std::string &buffer, CheatEntry &entry)
    {
        for (TableSetter* setter : this->setters)
        {
            setter->set(buffer, entry);
        }
    }
}
