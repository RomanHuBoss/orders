--
-- PostgreSQL database dump
--

-- Dumped from database version 9.4.19
-- Dumped by pg_dump version 9.6.0

-- Started on 2019-07-25 13:46:52

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 2101 (class 1262 OID 16384)
-- Name: orders; Type: DATABASE; Schema: -; Owner: postgres
--

CREATE DATABASE orders WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'Russian_Russia.1251' LC_CTYPE = 'Russian_Russia.1251';


ALTER DATABASE orders OWNER TO postgres;

\connect orders

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 1 (class 3079 OID 11855)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2104 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 184 (class 1259 OID 16504)
-- Name: comments; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE comments (
    id integer NOT NULL,
    pid integer,
    id_task integer NOT NULL,
    id_worker integer NOT NULL,
    comment text NOT NULL,
    published_dt timestamp with time zone NOT NULL
);


ALTER TABLE comments OWNER TO postgres;

--
-- TOC entry 2105 (class 0 OID 0)
-- Dependencies: 184
-- Name: TABLE comments; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE comments IS 'Название: Комментарии';


--
-- TOC entry 2106 (class 0 OID 0)
-- Dependencies: 184
-- Name: COLUMN comments.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.id IS 'Идентификатор комментария';


--
-- TOC entry 2107 (class 0 OID 0)
-- Dependencies: 184
-- Name: COLUMN comments.pid; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.pid IS 'Идентификатор родительского комментария';


--
-- TOC entry 2108 (class 0 OID 0)
-- Dependencies: 184
-- Name: COLUMN comments.id_task; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.id_task IS 'Идентификатор задачи';


--
-- TOC entry 2109 (class 0 OID 0)
-- Dependencies: 184
-- Name: COLUMN comments.id_worker; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.id_worker IS 'Идентификатор автора комментария';


--
-- TOC entry 2110 (class 0 OID 0)
-- Dependencies: 184
-- Name: COLUMN comments.comment; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.comment IS 'Содержимое комментария';


--
-- TOC entry 2111 (class 0 OID 0)
-- Dependencies: 184
-- Name: COLUMN comments.published_dt; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.published_dt IS 'Дата и время публикации';


--
-- TOC entry 183 (class 1259 OID 16502)
-- Name: comments_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE comments_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE comments_id_seq OWNER TO postgres;

--
-- TOC entry 2112 (class 0 OID 0)
-- Dependencies: 183
-- Name: comments_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE comments_id_seq OWNED BY comments.id;


--
-- TOC entry 178 (class 1259 OID 16409)
-- Name: department_workers; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE department_workers (
    id integer NOT NULL,
    fio text NOT NULL,
    login text NOT NULL,
    password text NOT NULL,
    id_position integer NOT NULL
);
ALTER TABLE ONLY department_workers ALTER COLUMN fio SET STATISTICS 0;
ALTER TABLE ONLY department_workers ALTER COLUMN login SET STATISTICS 0;
ALTER TABLE ONLY department_workers ALTER COLUMN password SET STATISTICS 0;


ALTER TABLE department_workers OWNER TO postgres;

--
-- TOC entry 2113 (class 0 OID 0)
-- Dependencies: 178
-- Name: TABLE department_workers; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE department_workers IS 'Название: Данные сотрудников отдела';


--
-- TOC entry 2114 (class 0 OID 0)
-- Dependencies: 178
-- Name: COLUMN department_workers.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN department_workers.id IS 'Идентификатор сотрудника';


--
-- TOC entry 2115 (class 0 OID 0)
-- Dependencies: 178
-- Name: COLUMN department_workers.fio; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN department_workers.fio IS 'Фамилия, имя, отчество';


--
-- TOC entry 2116 (class 0 OID 0)
-- Dependencies: 178
-- Name: COLUMN department_workers.login; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN department_workers.login IS 'Логин';


--
-- TOC entry 2117 (class 0 OID 0)
-- Dependencies: 178
-- Name: COLUMN department_workers.password; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN department_workers.password IS 'Пароль';


--
-- TOC entry 2118 (class 0 OID 0)
-- Dependencies: 178
-- Name: COLUMN department_workers.id_position; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN department_workers.id_position IS 'Идентификатор должности';


--
-- TOC entry 177 (class 1259 OID 16407)
-- Name: department_workers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE department_workers_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE department_workers_id_seq OWNER TO postgres;

--
-- TOC entry 2119 (class 0 OID 0)
-- Dependencies: 177
-- Name: department_workers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE department_workers_id_seq OWNED BY department_workers.id;


--
-- TOC entry 186 (class 1259 OID 16535)
-- Name: positions; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE positions (
    id integer NOT NULL,
    title text NOT NULL,
    description text,
    is_head boolean DEFAULT false NOT NULL
);


ALTER TABLE positions OWNER TO postgres;

--
-- TOC entry 2120 (class 0 OID 0)
-- Dependencies: 186
-- Name: COLUMN positions.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN positions.id IS 'Идентификатор должности';


--
-- TOC entry 2121 (class 0 OID 0)
-- Dependencies: 186
-- Name: COLUMN positions.title; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN positions.title IS 'Название должности';


--
-- TOC entry 2122 (class 0 OID 0)
-- Dependencies: 186
-- Name: COLUMN positions.description; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN positions.description IS 'Описание должности';


--
-- TOC entry 2123 (class 0 OID 0)
-- Dependencies: 186
-- Name: COLUMN positions.is_head; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN positions.is_head IS 'Признак начальника подразделения';


--
-- TOC entry 185 (class 1259 OID 16533)
-- Name: positions_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE positions_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE positions_id_seq OWNER TO postgres;

--
-- TOC entry 2124 (class 0 OID 0)
-- Dependencies: 185
-- Name: positions_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE positions_id_seq OWNED BY positions.id;


--
-- TOC entry 174 (class 1259 OID 16387)
-- Name: projects; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE projects (
    id integer NOT NULL,
    title text NOT NULL,
    description text
);


ALTER TABLE projects OWNER TO postgres;

--
-- TOC entry 2125 (class 0 OID 0)
-- Dependencies: 174
-- Name: TABLE projects; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE projects IS 'Название: Проекты';


--
-- TOC entry 2126 (class 0 OID 0)
-- Dependencies: 174
-- Name: COLUMN projects.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN projects.id IS 'Идентификатор проекта';


--
-- TOC entry 2127 (class 0 OID 0)
-- Dependencies: 174
-- Name: COLUMN projects.title; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN projects.title IS 'Название проекта';


--
-- TOC entry 2128 (class 0 OID 0)
-- Dependencies: 174
-- Name: COLUMN projects.description; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN projects.description IS 'Описание проекта';


--
-- TOC entry 173 (class 1259 OID 16385)
-- Name: projects_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE projects_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE projects_id_seq OWNER TO postgres;

--
-- TOC entry 2129 (class 0 OID 0)
-- Dependencies: 173
-- Name: projects_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE projects_id_seq OWNED BY projects.id;


--
-- TOC entry 181 (class 1259 OID 16452)
-- Name: status_to_status; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE status_to_status (
    id_status_old integer NOT NULL,
    id_status_new integer NOT NULL,
    is_head_only boolean DEFAULT false NOT NULL,
    CONSTRAINT status_to_status_chk CHECK ((id_status_old <> id_status_new))
);
ALTER TABLE ONLY status_to_status ALTER COLUMN id_status_new SET STATISTICS 0;


ALTER TABLE status_to_status OWNER TO postgres;

--
-- TOC entry 2130 (class 0 OID 0)
-- Dependencies: 181
-- Name: COLUMN status_to_status.id_status_old; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN status_to_status.id_status_old IS 'Идентификатор старого статуса';


--
-- TOC entry 2131 (class 0 OID 0)
-- Dependencies: 181
-- Name: COLUMN status_to_status.id_status_new; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN status_to_status.id_status_new IS 'Идентификатор нового статуса';


--
-- TOC entry 2132 (class 0 OID 0)
-- Dependencies: 181
-- Name: COLUMN status_to_status.is_head_only; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN status_to_status.is_head_only IS 'Разрешено только для руководителя отдела';


--
-- TOC entry 2133 (class 0 OID 0)
-- Dependencies: 181
-- Name: CONSTRAINT status_to_status_chk ON status_to_status; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON CONSTRAINT status_to_status_chk ON status_to_status IS 'Статусы не должны совпадать';


--
-- TOC entry 176 (class 1259 OID 16398)
-- Name: statuses; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE statuses (
    id integer NOT NULL,
    title text NOT NULL,
    is_initial boolean DEFAULT false NOT NULL,
    is_final boolean DEFAULT false NOT NULL,
    is_working boolean DEFAULT false NOT NULL,
    is_need_rework boolean DEFAULT false NOT NULL,
    is_declined boolean DEFAULT false NOT NULL,
    is_checking boolean DEFAULT false NOT NULL
);


ALTER TABLE statuses OWNER TO postgres;

--
-- TOC entry 2134 (class 0 OID 0)
-- Dependencies: 176
-- Name: TABLE statuses; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE statuses IS 'Название: Статусы задач';


--
-- TOC entry 2135 (class 0 OID 0)
-- Dependencies: 176
-- Name: COLUMN statuses.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.id IS 'Идентификатор статуса';


--
-- TOC entry 2136 (class 0 OID 0)
-- Dependencies: 176
-- Name: COLUMN statuses.title; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.title IS 'Название статуса';


--
-- TOC entry 2137 (class 0 OID 0)
-- Dependencies: 176
-- Name: COLUMN statuses.is_initial; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_initial IS 'Признак статуса новой задачи';


--
-- TOC entry 2138 (class 0 OID 0)
-- Dependencies: 176
-- Name: COLUMN statuses.is_final; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_final IS 'Признак статуса завершенной задачи';


--
-- TOC entry 2139 (class 0 OID 0)
-- Dependencies: 176
-- Name: COLUMN statuses.is_working; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_working IS 'Признак статуса разрабатываемой задачи';


--
-- TOC entry 2140 (class 0 OID 0)
-- Dependencies: 176
-- Name: COLUMN statuses.is_need_rework; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_need_rework IS 'Признак статуса задачи, которую нужно доработать';


--
-- TOC entry 2141 (class 0 OID 0)
-- Dependencies: 176
-- Name: COLUMN statuses.is_declined; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_declined IS 'Признак статуса отмененной задачи';


--
-- TOC entry 2142 (class 0 OID 0)
-- Dependencies: 176
-- Name: COLUMN statuses.is_checking; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_checking IS 'Признак статуса проверяемой задачи';


--
-- TOC entry 175 (class 1259 OID 16396)
-- Name: statuses_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE statuses_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE statuses_id_seq OWNER TO postgres;

--
-- TOC entry 2143 (class 0 OID 0)
-- Dependencies: 175
-- Name: statuses_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE statuses_id_seq OWNED BY statuses.id;


--
-- TOC entry 182 (class 1259 OID 16476)
-- Name: task_statuses_history; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE task_statuses_history (
    id_task integer NOT NULL,
    id_status integer NOT NULL,
    id_worker integer NOT NULL,
    status_dt timestamp with time zone DEFAULT now() NOT NULL
);


ALTER TABLE task_statuses_history OWNER TO postgres;

--
-- TOC entry 2144 (class 0 OID 0)
-- Dependencies: 182
-- Name: TABLE task_statuses_history; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE task_statuses_history IS 'Название: История изменения статусов задачи';


--
-- TOC entry 2145 (class 0 OID 0)
-- Dependencies: 182
-- Name: COLUMN task_statuses_history.id_task; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN task_statuses_history.id_task IS 'Идентификатор задачи';


--
-- TOC entry 2146 (class 0 OID 0)
-- Dependencies: 182
-- Name: COLUMN task_statuses_history.id_status; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN task_statuses_history.id_status IS 'Идентификатор статуса';


--
-- TOC entry 2147 (class 0 OID 0)
-- Dependencies: 182
-- Name: COLUMN task_statuses_history.id_worker; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN task_statuses_history.id_worker IS 'Идентификатор установившего';


--
-- TOC entry 2148 (class 0 OID 0)
-- Dependencies: 182
-- Name: COLUMN task_statuses_history.status_dt; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN task_statuses_history.status_dt IS 'Время и дата установки статуса';


--
-- TOC entry 180 (class 1259 OID 16422)
-- Name: tasks; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE tasks (
    id integer NOT NULL,
    pid integer,
    id_project integer NOT NULL,
    id_worker integer NOT NULL,
    title text NOT NULL,
    description text NOT NULL,
    deadline_dt timestamp with time zone NOT NULL,
    published_dt timestamp with time zone DEFAULT now() NOT NULL
);


ALTER TABLE tasks OWNER TO postgres;

--
-- TOC entry 2149 (class 0 OID 0)
-- Dependencies: 180
-- Name: TABLE tasks; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE tasks IS 'Название: Задачи';


--
-- TOC entry 2150 (class 0 OID 0)
-- Dependencies: 180
-- Name: COLUMN tasks.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.id IS 'Идентификатор задачи';


--
-- TOC entry 2151 (class 0 OID 0)
-- Dependencies: 180
-- Name: COLUMN tasks.pid; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.pid IS 'Идентификатор родительской задачи';


--
-- TOC entry 2152 (class 0 OID 0)
-- Dependencies: 180
-- Name: COLUMN tasks.id_project; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.id_project IS 'Идентификатор проекта';


--
-- TOC entry 2153 (class 0 OID 0)
-- Dependencies: 180
-- Name: COLUMN tasks.id_worker; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.id_worker IS 'Идентификатор сотрудника';


--
-- TOC entry 2154 (class 0 OID 0)
-- Dependencies: 180
-- Name: COLUMN tasks.title; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.title IS 'Название задачи';


--
-- TOC entry 2155 (class 0 OID 0)
-- Dependencies: 180
-- Name: COLUMN tasks.description; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.description IS 'Описание задачи';


--
-- TOC entry 2156 (class 0 OID 0)
-- Dependencies: 180
-- Name: COLUMN tasks.deadline_dt; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.deadline_dt IS 'Планируемая дата окончания';


--
-- TOC entry 2157 (class 0 OID 0)
-- Dependencies: 180
-- Name: COLUMN tasks.published_dt; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.published_dt IS 'Дата и время публикации задачи';


--
-- TOC entry 179 (class 1259 OID 16420)
-- Name: tasks_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE tasks_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE tasks_id_seq OWNER TO postgres;

--
-- TOC entry 2158 (class 0 OID 0)
-- Dependencies: 179
-- Name: tasks_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE tasks_id_seq OWNED BY tasks.id;


--
-- TOC entry 1939 (class 2604 OID 16507)
-- Name: comments id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY comments ALTER COLUMN id SET DEFAULT nextval('comments_id_seq'::regclass);


--
-- TOC entry 1933 (class 2604 OID 16412)
-- Name: department_workers id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY department_workers ALTER COLUMN id SET DEFAULT nextval('department_workers_id_seq'::regclass);


--
-- TOC entry 1940 (class 2604 OID 16538)
-- Name: positions id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY positions ALTER COLUMN id SET DEFAULT nextval('positions_id_seq'::regclass);


--
-- TOC entry 1925 (class 2604 OID 16390)
-- Name: projects id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY projects ALTER COLUMN id SET DEFAULT nextval('projects_id_seq'::regclass);


--
-- TOC entry 1926 (class 2604 OID 16401)
-- Name: statuses id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY statuses ALTER COLUMN id SET DEFAULT nextval('statuses_id_seq'::regclass);


--
-- TOC entry 1934 (class 2604 OID 16425)
-- Name: tasks id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY tasks ALTER COLUMN id SET DEFAULT nextval('tasks_id_seq'::regclass);


--
-- TOC entry 2094 (class 0 OID 16504)
-- Dependencies: 184
-- Data for Name: comments; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY comments (id, pid, id_task, id_worker, comment, published_dt) FROM stdin;
\.


--
-- TOC entry 2159 (class 0 OID 0)
-- Dependencies: 183
-- Name: comments_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('comments_id_seq', 1, false);


--
-- TOC entry 2088 (class 0 OID 16409)
-- Dependencies: 178
-- Data for Name: department_workers; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY department_workers (id, fio, login, password, id_position) FROM stdin;
2	Начальник подразделения	admin	21232f297a57a5a743894a0e4a801fc3	1
3	Иванов Иван Иванович	ivanov	4dfe6e220d16e7b633cfdd92bcc8050b	2
\.


--
-- TOC entry 2160 (class 0 OID 0)
-- Dependencies: 177
-- Name: department_workers_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('department_workers_id_seq', 3, true);


--
-- TOC entry 2096 (class 0 OID 16535)
-- Dependencies: 186
-- Data for Name: positions; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY positions (id, title, description, is_head) FROM stdin;
1	Начальник отдела	\N	t
2	Аналитик	\N	f
3	Программист	\N	f
\.


--
-- TOC entry 2161 (class 0 OID 0)
-- Dependencies: 185
-- Name: positions_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('positions_id_seq', 3, true);


--
-- TOC entry 2084 (class 0 OID 16387)
-- Dependencies: 174
-- Data for Name: projects; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY projects (id, title, description) FROM stdin;
1	Тестовый проект	Разработка тестового IT-проекта
\.


--
-- TOC entry 2162 (class 0 OID 0)
-- Dependencies: 173
-- Name: projects_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('projects_id_seq', 1, true);


--
-- TOC entry 2091 (class 0 OID 16452)
-- Dependencies: 181
-- Data for Name: status_to_status; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY status_to_status (id_status_old, id_status_new, is_head_only) FROM stdin;
1	3	f
1	5	t
2	4	t
3	1	f
3	5	t
3	6	f
4	3	f
4	5	t
5	1	t
6	4	t
6	5	t
6	2	t
\.


--
-- TOC entry 2086 (class 0 OID 16398)
-- Dependencies: 176
-- Data for Name: statuses; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY statuses (id, title, is_initial, is_final, is_working, is_need_rework, is_declined, is_checking) FROM stdin;
1	Нужно сделать	t	f	f	f	f	f
2	Выполнено	f	t	f	f	f	f
3	В работе	f	f	t	f	f	f
4	Нужна доработка	f	f	f	t	f	f
5	Отменено	f	f	f	f	t	f
6	На проверке	f	f	f	f	f	t
\.


--
-- TOC entry 2163 (class 0 OID 0)
-- Dependencies: 175
-- Name: statuses_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('statuses_id_seq', 6, true);


--
-- TOC entry 2092 (class 0 OID 16476)
-- Dependencies: 182
-- Data for Name: task_statuses_history; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY task_statuses_history (id_task, id_status, id_worker, status_dt) FROM stdin;
\.


--
-- TOC entry 2090 (class 0 OID 16422)
-- Dependencies: 180
-- Data for Name: tasks; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY tasks (id, pid, id_project, id_worker, title, description, deadline_dt, published_dt) FROM stdin;
\.


--
-- TOC entry 2164 (class 0 OID 0)
-- Dependencies: 179
-- Name: tasks_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('tasks_id_seq', 1, false);


--
-- TOC entry 1957 (class 2606 OID 16512)
-- Name: comments comments_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY comments
    ADD CONSTRAINT comments_pkey PRIMARY KEY (id);


--
-- TOC entry 1947 (class 2606 OID 16419)
-- Name: department_workers department_workers_login_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY department_workers
    ADD CONSTRAINT department_workers_login_key UNIQUE (login);


--
-- TOC entry 1949 (class 2606 OID 16417)
-- Name: department_workers department_workers_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY department_workers
    ADD CONSTRAINT department_workers_pkey PRIMARY KEY (id);


--
-- TOC entry 1959 (class 2606 OID 16543)
-- Name: positions positions_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY positions
    ADD CONSTRAINT positions_pkey PRIMARY KEY (id);


--
-- TOC entry 1961 (class 2606 OID 16545)
-- Name: positions positions_title_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY positions
    ADD CONSTRAINT positions_title_key UNIQUE (title);


--
-- TOC entry 1943 (class 2606 OID 16395)
-- Name: projects projects_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY projects
    ADD CONSTRAINT projects_pkey PRIMARY KEY (id);


--
-- TOC entry 1953 (class 2606 OID 16456)
-- Name: status_to_status status_to_status_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY status_to_status
    ADD CONSTRAINT status_to_status_pkey PRIMARY KEY (id_status_new, id_status_old);


--
-- TOC entry 1945 (class 2606 OID 16406)
-- Name: statuses statuses_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY statuses
    ADD CONSTRAINT statuses_pkey PRIMARY KEY (id);


--
-- TOC entry 1955 (class 2606 OID 16481)
-- Name: task_statuses_history task_statuses_history_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY task_statuses_history
    ADD CONSTRAINT task_statuses_history_pkey PRIMARY KEY (id_task, id_status, status_dt, id_worker);


--
-- TOC entry 1951 (class 2606 OID 16431)
-- Name: tasks tasks_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY tasks
    ADD CONSTRAINT tasks_pkey PRIMARY KEY (id);


--
-- TOC entry 1971 (class 2606 OID 16518)
-- Name: comments comments_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY comments
    ADD CONSTRAINT comments_fk FOREIGN KEY (pid) REFERENCES comments(id) ON DELETE CASCADE;


--
-- TOC entry 1972 (class 2606 OID 16523)
-- Name: comments comments_fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY comments
    ADD CONSTRAINT comments_fk1 FOREIGN KEY (id_task) REFERENCES tasks(id) ON DELETE CASCADE;


--
-- TOC entry 1973 (class 2606 OID 16528)
-- Name: comments comments_fk2; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY comments
    ADD CONSTRAINT comments_fk2 FOREIGN KEY (id_worker) REFERENCES department_workers(id) ON DELETE CASCADE;


--
-- TOC entry 1962 (class 2606 OID 16553)
-- Name: department_workers department_workers_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY department_workers
    ADD CONSTRAINT department_workers_fk FOREIGN KEY (id_position) REFERENCES positions(id) ON DELETE CASCADE;


--
-- TOC entry 1966 (class 2606 OID 16457)
-- Name: status_to_status status_to_status_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY status_to_status
    ADD CONSTRAINT status_to_status_fk FOREIGN KEY (id_status_old) REFERENCES statuses(id) ON DELETE CASCADE;


--
-- TOC entry 1967 (class 2606 OID 16467)
-- Name: status_to_status status_to_status_fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY status_to_status
    ADD CONSTRAINT status_to_status_fk1 FOREIGN KEY (id_status_new) REFERENCES statuses(id) ON DELETE CASCADE;


--
-- TOC entry 1968 (class 2606 OID 16482)
-- Name: task_statuses_history task_statuses_history_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY task_statuses_history
    ADD CONSTRAINT task_statuses_history_fk FOREIGN KEY (id_task) REFERENCES tasks(id) ON DELETE CASCADE;


--
-- TOC entry 1969 (class 2606 OID 16492)
-- Name: task_statuses_history task_statuses_history_fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY task_statuses_history
    ADD CONSTRAINT task_statuses_history_fk1 FOREIGN KEY (id_status) REFERENCES statuses(id) ON DELETE CASCADE;


--
-- TOC entry 1970 (class 2606 OID 16497)
-- Name: task_statuses_history task_statuses_history_fk2; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY task_statuses_history
    ADD CONSTRAINT task_statuses_history_fk2 FOREIGN KEY (id_worker) REFERENCES department_workers(id) ON DELETE CASCADE;


--
-- TOC entry 1963 (class 2606 OID 16432)
-- Name: tasks tasks_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY tasks
    ADD CONSTRAINT tasks_fk FOREIGN KEY (pid) REFERENCES tasks(id) ON DELETE CASCADE;


--
-- TOC entry 1964 (class 2606 OID 16442)
-- Name: tasks tasks_fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY tasks
    ADD CONSTRAINT tasks_fk1 FOREIGN KEY (id_project) REFERENCES projects(id) ON DELETE CASCADE;


--
-- TOC entry 1965 (class 2606 OID 16447)
-- Name: tasks tasks_fk2; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY tasks
    ADD CONSTRAINT tasks_fk2 FOREIGN KEY (id_worker) REFERENCES department_workers(id) ON DELETE CASCADE;


--
-- TOC entry 2103 (class 0 OID 0)
-- Dependencies: 6
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2019-07-25 13:46:54

--
-- PostgreSQL database dump complete
--

