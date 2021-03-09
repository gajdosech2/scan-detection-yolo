/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_DIALOGS_H
#define UTILS_DIALOGS_H
#include <string>

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <iostream>
#endif // _WIN32

#include <Utils/ExtSTD.h>


//! Dialog message boxes wrapper functions.
namespace dialog
{

  //! Shows error dialog and displays message. Program waits until user confirms.
  inline void Error(const std::string &msg, const std::string &title = "Error")
  {
    const std::wstring msgW = std_ext::ToWString(msg);
    const std::wstring titleW = std_ext::ToWString(title);
#ifdef _WIN32
    MessageBox(0, msgW.c_str(), titleW.c_str(), MB_OK | MB_ICONERROR | MB_TASKMODAL);
#elif __linux__
    std::cout << "Title:" << title << std::endl;
    std::cout << "Message:" << msg << std::endl;
#else
#error "platform not supported"
#endif
  }

  //! Show warning dialog and displays message. Program waits until user confirms.
  inline void Warning(const std::string &msg, const std::string &title = "Warning")
  {
    const std::wstring msgW = std_ext::ToWString(msg);
    const std::wstring titleW = std_ext::ToWString(title);
#ifdef _WIN32
    MessageBox(0, msgW.c_str(), titleW.c_str(), MB_OK | MB_ICONWARNING | MB_TASKMODAL);
#elif __linux__
    std::cout << "Title:" << title << std::endl;
    std::cout << "Message:" << msg << std::endl;
#else
#error "platform not supported"
#endif
  }

  //! Show information dialog with specified message. Program waits until user confirms.
  inline void Info(const std::string &msg, const std::string &title = "Information")
  {
    const std::wstring msgW = std_ext::ToWString(msg);
    const std::wstring titleW = std_ext::ToWString(title);
#ifdef _WIN32
    MessageBox(0, msgW.c_str(), titleW.c_str(), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
#elif __linux__
    std::cout << "Title:" << title << std::endl;
    std::cout << "Message:" << msg << std::endl;
#else
#error "platform not supported"
#endif
  }

  //! Show dialog with YES and NO buttons and returns answer. Program waits until user selects answer.
  inline bool Confirmation(const std::string &question, const std::string &title = "Confirmation")
  {
    const std::wstring questionW = std_ext::ToWString(question);
    const std::wstring titleW = std_ext::ToWString(title);
#ifdef _WIN32
    const int result = MessageBox(0, questionW.c_str(), titleW.c_str(), MB_YESNO | MB_TASKMODAL);
    return result == IDYES;
#elif __linux__
    std::cout << "implement me" << std::endl;
    return false;
#else
#error "platform not supported"
#endif
  }

}

#endif /* !UTILS_DIALOGS_H */