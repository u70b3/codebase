// file reader
/*

f, err := os.Open("/test.txt")
if err != nil {
    panic(err)
}
defer f.Close()
fd, err := ioutil.ReadAll(f)
if err != nil {
    panic(err)
}
fmt.Println(string(fd))

*/



// file writer
/*
func writeFile(path string, b []byte) {
    file, err := os.OpenFile(path, os.O_WRONLY|os.O_TRUNC|os.O_CREATE, 0777)
    defer file.Close()

    if err != nil {
        panic(err)
    }

    file.Write(b)
}
*/

// file list
/*
func getFilelist(r string) {
    err := filepath.Walk(r, func(p string, f os.FileInfo, err error) error {
        if f == nil {
            return nil
        }
        if p == r || f.IsDir() {
            return nil
        }
        fmt.Println(p)
        return nil
    })
    if err != nil {
        fmt.Printf("filepath.Walk() returned %v\n", err)
    }
}
*/

// timer
/*
duration := 2 * time.Second
timer := time.NewTimer(duration)
go func() {
    for {
        select {
        case <-timer.C:
            fmt.Println("here")
            timer.Reset(duration)
        }
    }
}()
*/
