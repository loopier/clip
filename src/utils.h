//
//  utils.h
//  clip
//
//  Created by roger on 11/08/2017.
//
//

#ifndef utils_h
#define utils_h

namespace loopier {
    namespace utils {
        /// \breif  Returns the name of the file without the extension
        string removeExtensionFromFilename(string & filename)
        {
            string name
            // check if name has extension
            std::size_t dotposition = name.find_last_of(".");
            if (dotposition == std::string::npos) {
                // has no dot.  Leave default extension (see constructor)
                return;
            }
            
            extension = name.substr(dotposition);
            ofLogVerbose() << __FUNCTION__ << ":\t" << name << "\t" << extension;
            name = name.substr(0, dotposition);
        }
        
        string getFileExtension
    }
}

#endif /* utils_h */
