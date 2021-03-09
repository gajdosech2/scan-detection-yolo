/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_DIALOG_INTERFACE_H
#define UTILS_DIALOG_INTERFACE_H

#include <string>
#include <optional>
#include <vector>

class IDialogInterface
{
public:
  virtual ~IDialogInterface() {}

  virtual std::optional<std::string> GetPathFromDirectorySelectionDialog(const std::wstring &title, const std::string &default_path = "") const = 0;
  virtual std::vector<std::string> GetPathsFromFileSelectionDialog(const std::wstring &title, const std::string &wildcard, bool enable_multiselect, const std::string &default_path = "") const = 0;
  virtual std::optional<std::string> GetPathFromFileSaveDialog(const std::wstring &title, const std::string &wildcard, bool overwrite_prompt_enabled, const std::string &default_path = "") const = 0;
  virtual void ShowErrorMessage(const std::wstring &message, const std::wstring &title = L"Message") const = 0;
  virtual void ShowWarningMessage(const std::wstring &message, const std::wstring &title = L"Message") const = 0;
  virtual void ShowInfoMessage(const std::wstring &message, const std::wstring &title = L"Message") const = 0;
  virtual bool ShowConfirmationDialog(const std::wstring &message, const std::wstring &title = L"Confirmation") const = 0;
};

#endif /* !UTILS_DIALOG_INTERFACE_H */