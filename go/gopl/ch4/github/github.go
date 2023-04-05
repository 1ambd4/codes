package main

import (
    "time"
    "encoding/json"
    "fmt"
    "os"
    "log"
    "net/http"
    "net/url"
    "strings"
    "html/template"
)

const IssuesURL = "https://api.github.com/search/issues"

type IssuesSearchResult struct {
    TotalCount int `json:"total_count"`
    Items      []*Issue
}

type Issue struct {
    Number      int
    HTMLURL     string `json:"html_url"`
    Title       string
    State       string
    User        *User
    CreateAt    time.Time   `json:"created_at"`
    Body        string
}

type User struct {
    Login       string
    HTMLURL     string `json:"html_url"`
}

func SearchIssues(terms []string) (*IssuesSearchResult, error) {
    q := url.QueryEscape(strings.Join(terms, " "))
    resp, err := http.Get(IssuesURL + "?q=" + q)
    if err != nil {
        return nil, err
    }

    if resp.StatusCode != http.StatusOK {
        resp.Body.Close()
        return nil, fmt.Errorf("search query failed: %s\n", resp.Status)
    }

    var result IssuesSearchResult
    if err := json.NewDecoder(resp.Body).Decode(&result); err != nil {
        resp.Body.Close()
        return nil, err
    }


    resp.Body.Close()
    return &result, nil
}

func daysAgo(t time.Time) int {
    return int(time.Since(t).Hours()/ 24)
}

func main() {
    // 普普通通的打印
    // result, err := SearchIssues(os.Args[1:])
    // if err != nil {
    //     log.Fatal(err)
    // }
    // fmt.Printf("%d issues:\n", result.TotalCount)
    // for _, item := range result.Items {
    //     fmt.Printf("#%-5d %9.9s %.55s\n",
    //                item.Number, item.User.Login, item.Title)
    // }


    // template/text
    // 自定义化程度高了一些
    // const templ = `
    // {{.TotalCount}} issues:
    // {{range .Items}}--------------------------------------
    // Number:    {{.Number}}
    // User:      {{.User.Login}}
    // Title:     {{.Title | printf "%.64s"}}
    // Age:       {{.CreateAt | daysAgo}} days
    // {{end}}`

    // var report = template.Must(template.New("issuelist").
    //                             Funcs(template.FuncMap{"daysAgo":daysAgo}).
    //                             Parse(templ))
    // result, err := SearchIssues(os.Args[1:])
    // if err != nil {
    //     log.Fatal(err)
    // }
    // if err := report.Execute(os.Stdout, result); err != nil {
    //     log.Fatal(err)
    // }

    // tmeplate/html
    // 数据绑定？？？？

    var report = template.Must(template.New("issuelist").Parse(`
    <h1>{{.TotalCount}} issues</h1>
    <table>
    <tr style='text-align: left'>
        <th>#</th>
        <th>State</th>
        <th>User</th>
        <th>Title</th>
    </tr>
    {{range .Items}}
    <tr>
        <td><a href='{{.HTMLURL}}'>{{.Number}}</a></td>
        <td>{{.State}}</td>
        <td><a href='{{.User.HTMLURL}}'>{{.User.Login}}</a></td>
        <td><a href='{{.HTMLURL}}'>{{.Title}}</a></td>
    {{end}}
    </table>
    `))

    result, err := SearchIssues(os.Args[1:])
    if err != nil {
        log.Fatal(err)
    }
    if err := report.Execute(os.Stdout, result); err != nil {
        log.Fatal(err)
    }
}
