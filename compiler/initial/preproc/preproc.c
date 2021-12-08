/**
 *
 *  Manage the preprocessor
 *
**/


// The first thing the preprocessor needs to do is combine all the files into a "mega input file"
// This is the combining format that the preprocessor is going to follow:
//
//
// (?) "<content>" represents random code, and "<import>" represents an importing narrative
//
// A file with this content:
//    ______________________________________________________
//   |                                                      |
//   |   <content>                                          |
//   |   <import>                                           |
//   |   <import>                                           |
//   |   <content>                                          |
//   |______________________________________________________|
//
// Will generate this "mega input file":
//    ______________________________________________________
//   |                                                      |
//   |   <content>                                          |
//   |   #file ./example1.stark ? /path/to/example1.stark   |
//   |   <content>                                          |
//   |   #endfile                                           |
//   |   #file ./example2.stark ? /path/to/example2.stark   |
//   |   <content>                                          |
//   |   #endfile                                           |
//   |   <content>                                          |
//   |______________________________________________________|
//
//
// In short words, the preprocessor is going to replace each line that includes an import narrative
// with two guiding lines with the content of the imported file placed between those two lines.
//
// The opening guiding line follows this format:
// "#file <!library name>/<relative file path> ? <absolute file path>"
// And the closing guiding line follows this format:
// "#endfile"
//
// Note that Import narratives can be nested. Also, only one import narrative is allowed per line,
// and no code is allowed to be placed in the same line with an import narrative.