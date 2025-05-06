#include "markdown.hpp"


int markdown::line_render(const std::string& line, std::string& html) {
    std::ostringstream oss;
    bool img = false;
    size_t ssi = 0;
    size_t si = 0;
    size_t ei = 0;
    while(1) {
        si = line.find("[", ssi);
        if (si != std::string::npos) {
            img = false;
            if (si > 0) {
                if (line[si - 1] == '!') {
                    img = true;
                }
            }
            if (img) {
                oss << yura::esc_html(line.substr(ssi, si - ssi - 1));
            } else {
                oss << yura::esc_html(line.substr(ssi, si - ssi));
            }
            si += 1;
            ei = line.find("]", si);
            if (ei != std::string::npos) {
                std::string name = line.substr(si, ei - si);
                si = ei + 1;
                ei = line.find("(", si);
                DP("si = " << si);
                DP("ei = " << ei);
                std::string url;
                if (si == ei) {
                    si = ei + 1;
                    ei = line.find(")", si);
                    if (ei != std::string::npos) {
                        url = line.substr(si, ei - si);
                        si = ei +1;
                    }
                }
                if (url.size() == 0) {
                    oss << "<a href='./" << yura::urlencode(name) << "'>" << name << "</a>";
                } else {
                    if (img) {
                        oss << "<img src='" << url << "' alt='" << name << "' />";
                    } else {
                        oss << "<a href='" << url << "'>" << name << "</a>";
                    }
                }
                ssi = si;
            } else {
                DP(line);
                DP("]がありません。");
                oss << line.substr(si);
                html = oss.str();
                return markdown::NG;
            }
        } else {
            // oss << line.substr(ssi);
            // ssi = si;
            break;
        }
    }
    oss << yura::esc_html(line.substr(ssi)) << "<br />" << std::endl;
    html = oss.str();
    return markdown::OK;
}


int markdown::render(const std::string& md, std::string& html) {
    std::istringstream iss(md);
    std::string line;
    std::vector<std::string> lines;
    std::ostringstream oss;
    DP("");
    while (std::getline(iss, line)) {
        lines.push_back(line);
    }
    int si = 0;
    for (auto l : lines) {
        si = l.find("###");
        if((si = l.find("###-")) == 0) {
            oss << "<h4>" << l.substr(4) << "</h4>" << std::endl;
        } else if((si = l.find("###")) == 0) {
            oss << "<h4>" << l.substr(3) << "</h4>" << std::endl;
        } else if((si = l.find("##-")) == 0) {
            oss << "<h3>" << l.substr(3) << "</h3>" << std::endl;
        } else if((si = l.find("##")) == 0) {
            oss << "<h3>" << l.substr(2) << "</h3>" << std::endl;
        } else if((si = l.find("#-")) == 0) {
            oss << "<h2>" << l.substr(2) << "</h2>" << std::endl;
        } else if((si = l.find("#")) == 0) {
            oss << "<h2>" << l.substr(1) << "</h2>" << std::endl;
        } else if((si = l.find("---")) == 0) {
            oss << "<hr/>" << std::endl;
        } else {
            std::string html;
            line_render(l, html);
            oss << html << std::endl;
        }
    }
    html = oss.str();
    return OK;
}

std::string markdown::html(const std::string& md) {
    std::string html;
    auto result = render(md, html);
    if (result) {
        DP("Error");
    }
    return html;
}
