package main

import (
  "fmt"
  "os"
  "path/filepath"
  "io/ioutil"
  "strings"
  "regexp"
  "bufio"
)

var (
  files []string
  basePath = "/tmp/analyze"
)

func WalkFunc(path string, info os.FileInfo, err error) error {
  if len(path) >= 3 {
    suffix1 := string([]byte(path)[len(path)-3:])
    suffix2 := string([]byte(path)[len(path)-2:])
    if (suffix2 == ".h" || suffix1 == ".cc") {
      files = append(files, path)
    }
  }
  return nil
}

func GetFiles(path string) {
  filepath.Walk(path, WalkFunc)
}

func ReadFileDeep(file string) []string {
  b, err := ioutil.ReadFile(file)
  if err != nil {
    fmt.Println(err)
  }
  str := string(b)
  reg := regexp.MustCompile(`include "*.+\.h"`)
  entrys := reg.FindAllString(str, -1)
  return entrys
}

func FindCompleteFile(entry string) string{
  var fileName string
  begin := false
  end := false
  for _, char := range entry {
    if char == '"' {
      if begin {
        end = true
      } else {
        begin = true
      }
      continue
    }
    if (begin && !end) {
      fileName += string(char)
    } 
  }
  return fileName
}

func DeepWalkFile(file string, deep int, filesWalked* []string) string {
  if len(file) == 0 {
    return ""
  }
  var res string
  res = (file + "\n") + res
  for i := 0; i < deep; i++ {
    res = " - " + res
  }
  entrys := ReadFileDeep(file)
  if len(entrys) != 0 {
    for _, entry := range entrys {
      var fileName string
      for _, file := range files {
        shortFileName := FindCompleteFile(entry)
        index := len(file)-len(shortFileName)
        if index >= 0 {
          fileTemp := file[index :]
          if shortFileName == fileTemp {
            if index - 1 >= 0 {
              if file[index-1:index] != "/" {
                continue
              } else {
                fileName = file
                break;
              }
            } else {
              fileName = file
              break;
            }
          }
        }
      }
      deepNew := deep + 1
      exist := false
      for _, fileWalked := range *filesWalked {
        if (fileWalked == fileName) {
          exist = true
          break
        }
      }
      if !exist {
        *filesWalked = append(*filesWalked, fileName)
        res += DeepWalkFile(fileName, deepNew, filesWalked)
      }
    }
    return res
  } else {
    return res
  }
}

func WalkFiles(files []string) {
  for _, file := range files {
    fmt.Println("==========" + file + "==========")
    var filesWalked []string
    res := DeepWalkFile(file, 0, &filesWalked)
    fmt.Println(res)

    fileName := strings.Replace(file, "/", "@", -1)
    WriteFile(res, basePath + "/" + fileName + ".md")
  }
}


func WriteFile(content string, filePath string) error {
  f, err := os.Create(filePath)
  if err != nil {
    return err 
  }   
  defer f.Close()
 
  w := bufio.NewWriter(f)
  fmt.Fprintln(w, content)
  return w.Flush()
}


func main() {
  os.RemoveAll(basePath)
  os.Mkdir(basePath, os.ModePerm)
  path := "."
  GetFiles(path)
  WalkFiles(files)
}
