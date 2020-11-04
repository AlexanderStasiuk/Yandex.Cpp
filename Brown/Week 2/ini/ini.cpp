#include "ini.h"

std::size_t Ini::Document::SectionCount() const {
    return sections.size();
}

const Ini::Section& Ini::Document::GetSection (const std::string& name) const {
    return sections.at(name);
}

Ini::Section& Ini::Document::AddSection(std::string name) {
    if (sections.count(name) > 0) {
        return sections.at(name);
    }
    Ini::Section new_section;
    sections[name] = new_section;
    return sections[name];
}

Ini::Document Ini::Load(std::istream& input) {
    Ini::Document document;
    std::string line;
    std::string section_name;
    Ini::Section* section;
    while (getline(input, line)) {
        if (line.size() == 0) {
            continue;
        }
        if (line[0] == '[') {
            section = &document.AddSection(std::string(line.begin()+1, line.end()-1));
            continue;
        } 
        
        section->insert({
            line.substr(0, line.find('=')),
            line.substr(line.find('=')+1, line.size()-2)
        });
        
    }
    return document;
}