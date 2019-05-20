#!/usr/bin/python
import subprocess
code_dir = "code"
title = "NTU ACM-ICPC Team Notebook"

def get_sections():
    sections = []
    section_name = None
    with open('contents.txt', 'r',encoding='utf-8') as f:
        for line in f:
            if '#' in line: line = line[:line.find('#')]
            line = line.strip()
            if len(line) == 0: continue
            if line[0] == '[':
                section_name = line[1:-1]
                subsections = []
                if section_name is not None:
                    sections.append((section_name, subsections))
            else:
                tmp = line.split('\t', 1)
                if len(tmp) == 1:
                    raise ValueError('Subsection parse error: %s' % line)
                filename = tmp[0]
                subsection_name = tmp[1]
                if section_name is None:
                    raise ValueError('Subsection given without section')
                subsections.append((filename, subsection_name))
    return sections

def get_style(filename):
    ext = filename.lower().split('.')[-1]
    if ext in ['c', 'cc', 'cpp']:
        return 'cpp'
    elif ext in ['java']:
        return 'java'
    elif ext in ['py']:
        return 'py'
    elif ext in ['tex']:
        return 'tex'
    else:
        return 'txt'

# TODO:  check if this is everything we need
def texify(s):
    #s = s.replace('\'', '\\\'')
    #s = s.replace('\"', '\\\"')
    return s

def get_tex(sections):
    tex = ''
    for (section_name, subsections) in sections:
        tex += '\\chapter{%s}\n' % texify(section_name)
        for (filename, subsection_name) in subsections:
            tex += '\\section{%s}\n' % texify(subsection_name)
            filetype = get_style(filename)
            if filetype == 'tex':
                tex += '\\raggedbottom\\input %s/%s\n' % (code_dir, filename)
            else:
                tex += '\\raggedbottom\\lstinputlisting[style=%s]{%s/%s}\n' % (get_style(filename), code_dir, filename)
            tex += '\\hrulefill\n'
        tex += '\n'
    return tex

if __name__ == "__main__":
    sections = get_sections()
    tex = get_tex(sections)
    with open('contents.tex', 'w', encoding='utf-8') as f:
        f.write(tex)
    latexmk_options = ["latexmk", "-xelatex", "ntudocument.tex"]
    subprocess.call(latexmk_options)